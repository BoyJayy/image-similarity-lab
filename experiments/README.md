# Image hash experiments

This directory contains small experiments for testing perceptual image hashes on modified and unrelated images.

The goal is to check how well different hashes survive common image transformations and where they start to fail.

## aHash

For the first experiment I used one original image and several modified versions of it:

- exact copies
- resized image
- JPEG recompression
- brighter image
- darker image
- cropped image
- rotated image

I also added several unrelated images for comparison.

All images are compared with `original.jpeg`.

The distance is calculated using Hamming distance between two 64-bit aHash values.

## Results

| Image | Same source | Hamming distance |
| --- | --- | ---: |
| copy | yes | 0 |
| copy2 | yes | 0 |
| resized | yes | 3 |
| compressed | yes | 0 |
| bright | yes | 6 |
| dark | yes | 1 |
| crop | yes | 14 |
| rotate | yes | 32 |
| different1 | no | 36 |
| different2 | no | 29 |
| different3 | no | 27 |
| different4 | no | 38 |
| different5 | no | 37 |

## Notes

aHash handled simple copies, resizing and JPEG recompression well.

Brightness changes also gave small distances in this experiment.

Cropping changed the hash more noticeably, but the distance was still lower than for unrelated images.

Rotation was the main problem. The rotated image had distance 32, while unrelated images had distances from 27 to 38.

This means that aHash is not rotation invariant. A single threshold cannot correctly classify both the rotated image and all unrelated images in this dataset.

If the rotated image is ignored, there is currently a clear gap:

- largest distance for modified versions: 14
- smallest distance for unrelated images: 27

This dataset is still very small, so it is too early to choose a fixed threshold from these results.

The same images will be used later to compare aHash with dHash and pHash.