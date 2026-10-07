#!/usr/bin/env python3
"""Tile the runner's .ppm screenshots into one contact sheet: sheet.py OUT.png SHOT.ppm..."""
import sys
from PIL import Image

shots = [Image.open(path) for path in sys.argv[2:]]
cols = min(len(shots), 4)
rows = (len(shots) + cols - 1) // cols
sheet = Image.new("RGB", (cols * 240, rows * 160))
for i, shot in enumerate(shots):
    sheet.paste(shot, (i % cols * 240, i // cols * 160))
sheet.save(sys.argv[1])
