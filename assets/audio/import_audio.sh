#!/bin/bash

# Batch import audio from the directory

AUDIO_DIR="assets/audio"
echo "Importing audio from $AUDIO_DIR..."

for audio_file in "$AUDIO_DIR"/*.{mp3,wav,ogg}; do
  echo "Importing audio: $audio_file"
  # Call the import command or tool for each audio file
  # Example: ./import_audio_tool $audio_file
done

echo "Audio import complete!"