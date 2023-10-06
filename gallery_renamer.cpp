#include "shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <filesystem>
#include <format>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <optional>
#include <string>
#include <utility>
#include <vector>

using namespace std::literals;

namespace fs = std::filesystem;

void rename_gallery(fs::path const& old_path, fs::path const& new_parent);

std::string choose_gallery_title(fs::path const& gallery);
std::optional<std::string> extract_title(fs::path const& info);
std::optional<std::string> extract_gallery_id(std::string const& title);

int main()
{
  std::ios::sync_with_stdio(false);

  std::cout << "Please enter the location of your galleries you want to rename "
               "(ex. C:\\downloads): ";
  std::string input;
  std::cin >> input;
  fs::path const src_dir{std::move(input)};

  std::cout
      << "Please enter the location you want to save your renamed galleries: ";
  std::cin >> input;
  fs::path const dst_dir{std::move(input)};

  if (!fs::is_directory(src_dir) || !fs::is_directory(dst_dir)) {
    std::cout << "locations not valid\n";
    return 1;
  }

  std::vector<fs::directory_entry> galleries{fs::directory_iterator{src_dir},
                                             fs::directory_iterator{}};
  if (fs::equivalent(src_dir, dst_dir)) {
    auto tmp_dir{std::filesystem::temp_directory_path() / std::tmpnam(nullptr)};
    while (fs::exists(tmp_dir))
      tmp_dir = std::filesystem::temp_directory_path() / std::tmpnam(nullptr);
    fs::create_directories(tmp_dir);

    for (auto&& i : galleries)
      if (fs::is_directory(i))
        rename_gallery(i.path(), tmp_dir);

    if (fs::equivalent(tmp_dir.root_name(), dst_dir.root_name())) {
      fs::remove_all(src_dir);
      fs::rename(tmp_dir, dst_dir);
    }
    else {
      fs::copy(tmp_dir, dst_dir, fs::copy_options::recursive);
      fs::remove_all(tmp_dir);
    }
  }
  else
    for (auto&& i : galleries)
      if (fs::is_directory(i))
        rename_gallery(i.path(), dst_dir);
}

void rename_gallery(fs::path const& old_path, fs::path const& new_parent)
{
  auto new_path{new_parent / choose_gallery_title(old_path)};
  fs::create_directories(new_path);

  std::vector<fs::path> images;
  for (auto&& i : fs::directory_iterator{old_path})
    if (i.path().filename() == "galleryinfo.txt")
      fs::rename(i.path(), new_path / "galleryinfo.txt");
    else
      images.push_back(i.path());

  std::ranges::sort(images, [](auto const& a, auto const& b) {
    return StrCmpLogicalW(a.filename().c_str(), b.filename().c_str()) == -1;
  });

  for (auto n{1}; auto&& i : images)
    fs::rename(i,
               new_path / std::format("{:0>3}{}", n++, i.extension().string()));
}

std::string choose_gallery_title(fs::path const& gallery)
{
  if (auto new_title{extract_title(gallery / "galleryinfo.txt")};
      new_title.has_value())
    if (auto id{extract_gallery_id(gallery.filename().string())};
        id.has_value())
      return new_title.value() + ' ' + id.value();
    else
      return new_title.value();
  return gallery.filename().string();
}

std::optional<std::string> extract_title(fs::path const& info)
{
  if (fs::exists(info)) {
    std::ifstream stream{info};
    std::string title;
    std::getline(stream, title);

    if (constexpr auto title_prefix{"Title:       "sv};
        title.starts_with(title_prefix)) {
      title.erase(0, size(title_prefix));
      std::ranges::replace_if(
          title,
          [](char c) {
            switch (c) {
            case '\\':
            case '/':
            case ':':
            case '*':
            case '?':
            case '"':
            case '<':
            case '>':
            case '|':
              return true;
            default:
              return false;
            }
          },
          ' ');
      return title;
    }
  }
  return {};
}

std::optional<std::string> extract_gallery_id(std::string const& title)
{
  if (ssize(title) > 2 && title[ssize(title) - 1] == ']'
      && isdigit(static_cast<unsigned char>(title[ssize(title) - 2]))) {
    auto i{ssize(title) - 3};
    while (i >= 0 && std::isdigit(static_cast<unsigned char>(title[i])))
      --i;
    if (i >= 0 && title[i] == '[')
      return title.substr(i);
  }
  return {};
}
