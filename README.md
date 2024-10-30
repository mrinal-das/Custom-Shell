# Custom-Shell
Here’s a detailed `README.md` template for your **Custom Shell in C** project. This document will showcase your project professionally on GitHub and make it easier for recruiters to understand the work you’ve done.

---

# **Custom Linux Shell in C** 🚀

Welcome to the **Custom Shell in C**, a simple yet powerful Linux shell created as part of a hands-on learning project. This shell supports basic UNIX commands, built-in functions, and pipeline execution, showcasing system programming concepts like **process management**, **system calls**, and **I/O redirection**.

---

## **Features** 🛠️

- **Built-in Commands**:
  - `cd` – Change directory.
  - `exit` – Exit the shell.
  - `help` – Display the help menu.
  - `hello` – Greet the user.

- **Pipeline Execution**:  
  Execute commands with pipes like `ls | grep filename`.

- **Command History**:  
  Previous commands are stored using the `readline` library, and they can be navigated using the arrow keys.

- **Error Handling**:  
  Handles failed processes and invalid commands gracefully.

---

## **Demo**

Here’s how the shell looks in action:

```bash
>>> cd /home/user/Desktop
Dir: /home/user/Desktop

>>> ls | grep project
project.c
project.txt

>>> hello
Hello user.
Mind that this is not a place to play around.
Use help to know more..

>>> exit
Goodbye
```

---

## **Installation & Setup** 📥

Follow these steps to compile and run the shell on your Linux machine:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/mrinal-das/custom-shell.git
   cd custom-shell
   ```

2. **Compile the Code**:
   ```bash
   gcc shell.c -o shell -lreadline
   ```

3. **Run the Shell**:
   ```bash
   ./shell
   ```

4. **Optional**: Install the `readline` library if not available:
   ```bash
   sudo pacman -S readline  # Arch-based systems
   sudo apt-get install libreadline-dev  # Debian/Ubuntu-based systems
   ```

---

## **How It Works** 🔍

1. **Startup**:  
   On launch, the shell greets the user and displays the username using the environment variable `$USER`.

2. **Command Execution**:  
   - **Simple Commands**: Commands like `ls`, `pwd`, `mkdir` are executed using `execvp()` after forking a child process.
   - **Built-in Commands**: The shell recognizes built-in commands (`cd`, `exit`, etc.) and handles them separately without creating a new process.

3. **Pipeline Support**:  
   Commands can be piped using `|`. For example, `ls | grep project` connects the output of `ls` to the input of `grep`.

4. **Error Handling**:  
   If a command fails, the shell outputs an error message (e.g., `Could not execute command`).

---

## **Project Structure** 📁

```
custom-shell/
│
├── shell.c           # Main source code for the shell
├── README.md         # Documentation (this file)
└── LICENSE           # License information (optional)
```

---

## **Technologies Used** 💻

- **Programming Language**: C  
- **Libraries**: `readline` (for input history)
- **Operating System**: Linux

---

## **Subjects Covered** 📚

This project demonstrates knowledge of:

1. **Operating Systems**:
   - Process management with `fork()`, `execvp()`, and `wait()`.
   - Handling pipelines with `pipe()` and `dup2()`.

2. **System Programming**:
   - System calls for creating and managing processes.
   - I/O redirection and inter-process communication (IPC).

3. **C Programming**:
   - Handling strings and pointers for command parsing.
   - Error handling and memory management.

4. **Linux Systems**:
   - Familiarity with common commands and shell behavior.
   - Environment variables like `$USER`.

---

## **How to Use the Shell** 🧑‍💻

- **List Files**:
  ```bash
  ls
  ```

- **Change Directory**:
  ```bash
  cd /path/to/directory
  ```

- **Execute Piped Commands**:
  ```bash
  ls | grep project
  ```

- **View Help**:
  ```bash
  help
  ```

- **Exit the Shell**:
  ```bash
  exit
  ```

---

## **Future Improvements** 🔮

- **Background Process Support**: Add support for `&` to run commands in the background.
- **Input/Output Redirection**: Implement support for `>` and `<` operators.
- **Multi-pipe Handling**: Extend the shell to support multiple pipes (e.g., `cmd1 | cmd2 | cmd3`).
- **Job Control**: Add features to suspend and resume jobs (e.g., `Ctrl+Z` and `bg`/`fg` commands).

---

## **Challenges Faced** 🧗

- **Process Management**: Learning how to fork processes and use `execvp()` efficiently.
- **Pipe Handling**: Redirecting input and output between processes using `pipe()` and `dup2()`.
- **Error Handling**: Ensuring the shell behaves gracefully when commands or processes fail.

---

## **Contributing** 🤝

Contributions are welcome! Feel free to fork this repository, submit issues, or create pull requests. 

1. Fork the repository.
2. Create a new branch:  
   ```bash
   git checkout -b feature-new-command
   ```
3. Make your changes and commit them:
   ```bash
   git commit -m "Add new feature"
   ```
4. Push to the branch:
   ```bash
   git push origin feature-new-command
   ```
5. Open a Pull Request on GitHub.

---



## **Acknowledgements** 🙌

Special thanks to **geeksforgeeks** for inspiring this project with the original shell implementation.

---

## **Contact** 📧

If you have any questions or suggestions, feel free to reach out:  
- **GitHub**: [mrianl-das](https://github.com/mrinal-das)
- **Email**: mrinaldaskarmakar@gmail.com

---

## **Conclusion**

This project demonstrates my knowledge of **C programming**, **system programming**, and **Linux internals**. It reflects my ability to design software at the **system level** and manage complex **process control flows**. Feel free to explore and use this project!

---

This `README.md` presents your project professionally, detailing its functionality, installation steps, technical subjects involved, and future improvements. Let me know if you want further customization!
