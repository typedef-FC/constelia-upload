# constelia.upload

Uploader for Linux. You can integrate this with Dolphin, or Thunar by seeing this [thread (click me)](https://constelia.ai/forums/index.php?threads/constelia-upload-linux-wrapper-for-i-constelia-ai-wayland-x11.10160/#post-81216).

## Usage

Place the file in the same directory as your `key.txt`. Assure you have execution permissions:
``` 
chmod +x constelia-upload
```

### Example:
```
./constelia-upload /home/typedef/Pictures/puppies.jpg
```

## Build
```
mkdir build && cd build && cmake .. && make
```