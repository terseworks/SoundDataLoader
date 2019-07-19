# SoundDataLoader

## About

This project was taken from a much larger game program currently in development. It shows how to load a WAV or XWMA file from disk, parse through the RIFF file format, copy the data to memory, then display information to the user. This data can then be used for sound buffers (not included in this project) such as those provided by DirectX Audio.

Using a parser to traverse through the RIFF data on an opened file has an advantage. You can store the positions of the data chunks for streaming or load everything to memory. This example performs the latter, which shouldn't be a problem with such a small file size.

If you happen to correctly guess the source of the sound clip in this project, I'd be quite impressed.

## Features

- Low-level Windows functions wrapped in classes, exposing a simple interface to work with.
- RIFF parser to scan through an opened file and mark the positions of each chunk of data.
- Encapsulated sound data ready to use.

## Code Usage

Feel free to use any part of this project for your own needs.
