# AdvisingAssistant

The problem I was solving was helping academic advisors in the Computer Science department at ABCU assist students more effectively during advising sessions. Advisors needed a tool that could quickly print a complete list of all computer science courses in alphanumeric order and, for any specific course, display its title and prerequisites. This would streamline the advising process and ensure students get accurate, comprehensive information about course requirements and sequencing.

I approached this by analyzing three different data structures: vectors, hash tables, and binary search trees. After looking at runtime complexity and what the system actually needed to do, I went with the binary search tree. This worked well because it gives O(log n) search times and keeps everything naturally sorted for when you need the full course list. Data structures matter because picking the wrong one can really slow down your program and frustrate users.

I ran into several challenges during development. Parsing CSV files was tricky because the formatting wasn't always consistent, so I had to build solid string handling. For prerequisite validation, I used a two-pass approach that loads all courses first, then checks that prerequisites actually exist. I also added error handling throughout for file operations and user input.

This project changed how I think about software design. Instead of just going with what I'm comfortable with, I now take time upfront to analyze what the program needs and pick the right tools for the job. I learned that how efficiently your algorithms run directly affects how well the application works for users.

My coding practices improved a lot through this work. I write more modular code now, breaking things into separate functions for different tasks like file handling, data management, and user interfaces. I focus on clear naming, handling edge cases properly, and keeping code organized so it's easier to modify later or work on with a team.

