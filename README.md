# gallery_renamer
A simple script to rename galleries.
- Only support Windows because I use [StrCmpLogicalW](https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-strcmplogicalw)
to determine the order of the images in the manga.
- H@H will shorten the name of the gallery title if it is too long.
This script will extract the title from galleryinfo.txt (if it exists) and replace the shortened title.

![image](https://github.com/cjt10136/gallery_renamer/assets/147172598/f69b7dd6-1bff-46d9-b35d-5d72154d8e42)


# Run
You should have a folder that contains all your galleries first, and then you can run this script on this folder.
This script will rename all the galleries in this folder for you and saves them to another folder.
![image](https://github.com/cjt10136/gallery_renamer/assets/147172598/e1350dbb-1773-4112-ae52-0ef77e781936)
![image](https://github.com/cjt10136/gallery_renamer/assets/147172598/ecfe4704-62c4-4ed6-a4f6-f9ebddde47f0)
