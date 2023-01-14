#!/bin/bash

mv README.html README.md
git add .
git commit -m "Changed README file"
git push origin main
mv README.md README.html 
