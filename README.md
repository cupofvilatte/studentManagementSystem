# Overview

This is the lowest level language in which I've developed a project. I think when you learn the lower level languages, it helps you further your abilities in higher level languages because you understand better how the computer is thinking. There where two primary purposes for building this software. The first was to explore C++ and become more comfortable in lower level syntax. The second was to develop and demonstrate competency with json data, loading, and saving data to a file from C++.

I wrote a program to manipulate student data. For this example, the included file is hardcoded into the program for demonstration purposes. This program includes several functions, including a main, menu, and loadData function. There are functions for each choice in the menu.

This program operates by displaying a menu and inviting the user to choose from options including view student data, add or delete students, add assignments, change grades, and calculate GPAs. All these choices dynamically affect the data file by reading and writing. The user provides input to influence the data. For example, if the user chooses to add a new user, that user will be added, in alphabetical order, to the json file.

This software demonstrates variables in C++. An example of this is in the menu and choice-oriented functions. Variables are saved and are updated through user input. This program showcases expressions in functions that determine grades by splitting the fraction into numerators and denomenators and then dividing to find the percentage. Conditionals are used for error handling through much of the code and in choice cases. For loops are used to iterate through classes and assignments to display to the console. Everything in this program is contained in functions. This program heavily uses maps and vectors to store information and to parse/serialize to connect with JSON.

{Provide a link to your YouTube demonstration. It should be a 4-5 minute demo of the software running and a walkthrough of the code. Focus should be on sharing what you learned about the language syntax.}

[Software Demo Video](http://youtube.link.goes.here)

# Development Environment

I used VSCode as a code editor because it has the microsoft C/C++ extension. I'm familiar with VSCode which made using it as a primary editor simple and effective.

I used my built in Clang++ Compiler, which is the default for Apple products, which I primarily use to code. It can be used with different versions. For my purposes, I used the most updated versions.

This program was in C++ Language. It is a low-level C-based coding language.

Libraries
- iostream: functionality for input and output. It allows me to use 'cin', 'cout', 'cerr', etc, which allow interaction from and display to the terminal.
- map: provides the map container, which is like a dictionary in other languages. It allows for key-value pairs.
- string: enables string usage, which is good for builting messages to output and storing string variables.
- vector: provides the vector container, which is like a list in other languages. It's a dynamic array.
- fstream: provides the tools for file input and output. This is what allows the program to load data from the json file and also to write to it.
- iomanip: provides several tools that help manipulate the input and output. Primary use in this program was to change how variables are stored (ex: only 2 decimal places of the gpa are stored.)
- "include/json.hpp": custom public tool which allows parsing and serializing of json data within C++.

# Useful Websites

- [w3schools.com](https://www.w3schools.com/cpp/)
- [Map in C++ YouTube Video with practical examples](https://youtu.be/aEgG4pidcKU?si=wtvlhpkCzXGHlF-R)
- [C++ Maps YouTube Video](https://youtu.be/agDPYyTsAH4?si=dPv9xq-U_O8_ngPb)
- [Effortless JSON in C++](https://youtu.be/3XubaLCDYOM?si=4XPouL7lFrsbplg7)
- [C++ Tutorial for Beginners](https://youtu.be/S3nx34WFXjI?si=Igv3Rb2NZrfbuM0K)
- [Stack Overflow](https://stackoverflow.com/questions/454762/vector-or-map-which-one-to-use)
- [ChatGPT](https://chatgpt.com/c/67001391-2078-800b-966f-9f0e492fc41c)

# Future Work

- Add Credit Amounts and display them
- Include Possible Course Codes with Classes
- Implement further functions to decrease redundancies
    - functions for class and assignment selection
    - function for gpa calculation implemented to assignment functions
- Determine letter grades using conditionals
- Create ability to add classes
    - This is currently semi-broken/necessary because if new students are added, there's no way to add assignments because they don't have classes