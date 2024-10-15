# Contributing to Sketch It

Thank you for considering contributing to Sketch It! We appreciate your time and effort in helping improve this project. Below are the guidelines to help ensure that your contribution is useful and easy to review.

## Getting Started

1. **Fork the repository**: Start by forking this repository and cloning it to your local machine.

   ```bash
   git clone https://github.com/RyanLarge13/sketch-it.git
   ```

2. **Set up your environment**: Follow the instructions in the `README.md` file to install dependencies and set up the project locally.

3. **Create a new branch**: Create a new branch for your contribution. Please use a descriptive name for your branch.

   Example:

   ```bash
   git checkout -b feature/new-feature-name
   ```

## Pull Request Guidelines

When submitting a pull request (PR), please ensure the following:

### 1. Descriptive Titles

- Use a clear and concise title for your pull request that describes the change you're making.
- Examples:
  - `Fix issue with form validation on signup page`
  - `Add pagination to blog posts`
  - `Improve performance of image compression`

### 2. Detailed Description

- **Clearly explain the purpose** of your PR in the description.
- **Reference related issues or tasks** by using keywords like `Fixes #issue-number` or `Closes #issue-number`.
- **Describe the changes** made in detail. Explain why these changes are necessary and what problem they solve.
- **Provide screenshots or GIFs** if your changes include UI updates, visual elements, or interactions.

  Example:

  ```markdown
  ## Description

  This PR adds pagination functionality to the blog posts. With this change, users can now navigate between pages to view more posts.

  - Added `getBlogPosts` API endpoint to retrieve posts with pagination.
  - Updated the frontend to include pagination controls.
  - Added unit tests for the pagination logic.

  Fixes #45.

  ## Screenshots

  ![pagination](url-to-screenshot)
  ```

### 3. Commit Messages

- Keep your commit messages clear and concise.
- Follow the format: `type(scope): message`.

  Examples:

  - `feat(blog): add pagination to blog posts`
  - `fix(auth): resolve token expiration issue`
  - `docs: update README with setup instructions`

### 4. Test Your Changes

- Ensure that your code works as expected by running any relevant tests.
- Write unit or integration tests for new features or bug fixes.
- If you're unsure how to write tests for your changes, mention it in the pull request, and we can assist.

### 5. Code Quality

- Ensure that your code adheres to the project's style guidelines (if applicable, mention linters, formatting tools, etc.).
- Run any automatic formatting tools or linters before submitting a pull request.

### 6. Keep Pull Requests Focused

- Limit each pull request to **one feature or bug fix**. This helps maintainers review and merge changes faster.
- If your PR addresses multiple issues or features, consider breaking it into smaller, more focused pull requests.

### 7. Stay Up to Date

- Before opening a pull request, make sure your branch is **up-to-date** with the `main` branch.
- Use the following commands to pull in the latest changes:

  ```bash
  git fetch origin
  git checkout main
  git merge origin/main
  ```

- If there are merge conflicts, resolve them locally before submitting your pull request.

## Review Process

1. Once your pull request is submitted, it will be reviewed by a project maintainer.
2. The maintainer may ask questions, request changes, or approve the PR.
3. If changes are requested, please update your pull request accordingly. Once the changes are made, a maintainer will review it again.

## Reporting Issues

If you encounter any issues or have suggestions, feel free to open an issue. Be sure to:

- Use a clear and descriptive title.
- Describe the issue or suggestion in detail.
- Provide steps to reproduce the issue if applicable.

Thank you for contributing to Sketch It! Your input helps make this project better for everyone.
