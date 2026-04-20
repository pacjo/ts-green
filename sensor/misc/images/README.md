# Images

- `.png` is the source of truth reference
- some useful actions can bdone with ImageMagick tools:
    - resize to display's 200x200:
        ```bash
        magick ./source.png -resize 200x200 -monochrome ./output.png
        ```
    - convert to `.bmp`:
        ```bash
        magick ./source.png -type bilevel ./output.bmp
        ```
