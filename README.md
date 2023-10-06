# gallery_renamer
A simple script to rename galleries.
- Only support Windows because I use [StrCmpLogicalW](https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-strcmplogicalw)
to determine the order of the images in the manga.
- H@H will shorten the name of the gallery title if it is too long.
This script will extract the title from galleryinfo.txt (if it exists) and replace the shortened title.

![image](https://github.com/cj2yt11/gallery_renamer/assets/147161189/fc38c620-db50-4ae7-b482-d92be287255f)

# Run
You should have a folder that contains all your galleries first, and then you can run this script on this folder.
This script will rename all the galleries in this folder for you and saves them to another folder.
![image](https://github.com/cj2yt11/gallery_renamer/assets/147161189/46c0d24e-f403-48ef-9342-fa586d272634)
![image](https://github.com/cj2yt11/gallery_renamer/assets/147161189/ffee41ef-885a-4d5b-b87d-3838f10cb0d3)

