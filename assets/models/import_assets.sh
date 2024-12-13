#!/bin/bash

# Batch import models from a directory

MODEL_DIR="assets/models"
echo "Importing models from $MODEL_DIR..."

for model_file in "$MODEL_DIR"/*.{obj,fbx,gltf}; do
  echo "Importing model: $model_file"
  # Call the import command or tool for each model
  # Example: ./import_model_tool $model_file
done

echo "Model import complete!"