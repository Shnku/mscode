# Guidelines for Assignment 1

1. Use functions and methods instead of writing the entire program in one block.
2. Use meaningful variable, class, function, and method names.
3. Add comments where necessary to explain important parts of the code.
4. Do not use Pandas or NumPy for this assignment.
5. Use Python's built-in modules such as `csv` and `json` where appropriate.
6. Your program must use Object-Oriented Programming with appropriate classes, attributes, constructors, and methods.
7. The program should be divided into at least 4 different `.py` files/modules. Do not place the complete implementation in a single Python file.
8. Use command-line arguments to run the program and/or provide the required input. Avoid hard-coding file names, modes, or other important inputs wherever possible.
9. Your program should support the required file operations for TXT, CSV, and JSON files.
10. Test your program with at least 5 student records.
11. Keep the code simple and readable. The purpose of this assignment is to understand Python programming concepts, not to create a highly complex application.
12. Do not copy a complete solution from the internet or another student. You should be able to explain your code during the lab evaluation.

---

# Suggested Project Structure

Your project should contain at least four Python files. For example:

```text
student-record-system/
│
├── data/
│   ├── students.txt
│   ├── students.csv
│   └── students.json
│
├── main.py
├── student.py
├── manager.py
├── file_handler.py
└── README.md

````

*(This is only a suggested structure. You may organize your files differently as long as the program contains at least four `.py` files and the responsibilities are reasonably separated.)*

---

## Command-Line Execution

The program should be executable from the command line. For example:

``` bash
python main.py --file students.csv --format csv

```

or:

``` bash
python main.py --file students.json --format json

```

* The exact command-line arguments and program design are up to you.
* You should use Python's `argparse` module or another appropriate approach for processing command-line arguments.
* The `README` file must clearly explain the commands required to run your program.

---

## Submission Requirements

### 1\. GitHub Repository

* Create a public GitHub repository containing your complete assignment.
* **Submit only the public GitHub repository link.**
* The repository should contain:
  * All `.py` source files
  * Required input/sample data files
  * `README.md`
  * Any other files required to run the program
* **Do not submit the project as a ZIP file unless specifically instructed.**

### 2\. README.md

The `README.md` file will serve as both the project documentation and report. It should contain the following sections:

* **A. Title:** Give an appropriate title to your project.
* **B. Objective:** Briefly explain the purpose of the assignment and what concepts were implemented.
* **C. Features:** List the major features implemented by your program (e.g., Student creation, Student search, Mark calculation, TXT file handling, CSV file handling, JSON file handling, etc.).
* **D. Project Structure:** Explain the purpose of each Python file.
  * *Example:*
    * `main.py` $\\rightarrow$ Command-line interface and program execution (single access point)
    * `student.py` $\\rightarrow$ Student class and student-related methods
    * `manager.py` $\\rightarrow$ Management of multiple student objects
    * `file_handler.py` $\\rightarrow$ Reading and writing files
* **E. Requirements:** Mention the software/environment required to run the program. Also mention any external packages if you have used any.
* **F. How to Run:** Clearly explain how to execute the program from the command line. Provide the actual commands required. If your program supports multiple modes, demonstrate each important mode.
  * *Example:* `python main.py --file students.csv --format csv`
* **G. Input and Output:** Briefly explain what inputs the program accepts, what files are required, what the program produces, and where output files are stored. You should include a few short examples of program output.
* **H. OOP Concepts Used:** Briefly explain where you have used:
  * Classes
  * Objects
  * Constructors
  * Attributes
  * Instance methods
  * Any other OOP concepts used
* **I. File Handling Concepts Used:** Explain how your program handles TXT, CSV, and JSON files, and mention the Python modules/functions used.
* **J. Sample Output:** Include a few screenshots or text examples showing that the program runs successfully.
* **K. Learning Outcome / Conclusion:** Write a short conclusion describing what you learned from the assignment and the difficulties you encountered.

---

## Submission Checklist

Before submitting your GitHub link, make sure that:

* [ ] The GitHub repository is public.
* [ ] The repository contains at least 4 `.py` files.
* [ ] The program uses classes and methods.
* [ ] TXT, CSV, and JSON file handling has been implemented.
* [ ] The program can be executed from the command line.
* [ ] Required inputs can be provided through command-line arguments.
* [ ] At least 5 student records have been tested.
* [ ] `README.md` contains the complete project documentation/report.
* [ ] `README` contains clear instructions for running the program.
* [ ] `README` explains the purpose of each Python file.
* [ ] Sample output/screenshots have been included.
* [ ] The repository does not contain unnecessary files such as Python cache files (`__pycache__`) or IDE-specific files.
* [ ] The submitted GitHub link is accessible without requiring permission.

---

## Cautionary Note

All guidelines and submission requirements are mandatory. Failure to fulfill any of the specified requirements may result in the submission being considered missing/incomplete, and no marks will be awarded.

If you have any doubts, you may communicate through the WhatsApp group. Please make sure that every requirement mentioned in this assignment is fulfilled before submission.
