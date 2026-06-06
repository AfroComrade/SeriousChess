#!/usr/bin/env bash

set -e

VENDOR_DIR="vendor"

declare -A REPOS=(
  ["SDL"]="https://github.com/libsdl-org/SDL.git"
  ["SDL_ttf"]="https://github.com/libsdl-org/SDL_ttf.git"
  ["SDL_image"]="https://github.com/libsdl-org/SDL_image.git"
  ["SDL_mixer"]="https://github.com/libsdl-org/SDL_mixer.git"
)

for name in "${!REPOS[@]}"; do
  repo="${REPOS[$name]}"
  dir="$VENDOR_DIR/$name"

  mkdir -p "$VENDOR_DIR"

  if [ -d "$dir/.git" ]; then
    echo "$name already exists — updating..."
    git -C "$dir" pull
  else
    echo "Cloning $name..."
    git clone "$repo" "$dir"
  fi
done

echo "All SDL dependencies ready."
