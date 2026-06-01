# CGRADES-Project

A C console-based student grade management system for recording and managing student quiz scores and activity grades. (HACKING-LIKE DESIGN EDITION?!)

## Features

- **Add Student** - Record student name and scores (Quiz 1, Quiz 2, Activity)
- **Show All Students** - Display all student records with calculated averages
- **Search Student** - Look up a student by their ID
- **Edit Student** - Update existing student scores
- **Delete Student** - Remove a student record
- **Persistent Storage** - Saves and loads data from `Student Records/students.txt`

## How It Works

- Each student has an auto-assigned ID, name, two quiz scores, and an activity score (0-100)
- The average is calculated as: `(Quiz1 + Quiz2 + Activity) / 3`
- Data is automatically saved to file after each modification
- Uses colored terminal output (Windows, ANSI escape codes)

## Compilation

```bash
gcc CGrades.c -o CGrades
```

## Note

This program is designed for Windows (uses `cls`, `system("mkdir ...")`, and `windows.h` for ANSI support).