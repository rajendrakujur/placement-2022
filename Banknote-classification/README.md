# 🏦 Banknote Classification Using Multi-Kernel SVM

This project implements and compares multiple Support Vector Machine (SVM) kernel techniques to classify banknotes as genuine or counterfeit using a dataset from the UCI Machine Learning Repository. A unique multi-kernel SVM approach is also explored through the combination of linear, polynomial, and RBF kernels.

---

## 📌 Table of Contents

* [Overview](#overview)
* [Dataset](#dataset)
* [Techniques Used](#techniques-used)
* [Project Structure](#project-structure)
* [Installation](#installation)
* [Usage](#usage)
* [Results](#results)
* [Limitations](#limitations)
* [Future Improvements](#future-improvements)

---

## 🧠 Overview

This project classifies banknotes based on image features extracted using wavelet transformations. It compares different SVM kernels (Linear, Polynomial, RBF, Sigmoid, Precomputed) and implements a **Multi-Kernel Learning (MKL)** approach that blends multiple kernels using a linear combination.

---

## 📂 Dataset

* **Source**: UCI Machine Learning Repository
* **Name**: [Data Banknote Authentication](https://archive.ics.uci.edu/dataset/267/banknote+authentication)
* **Size**: 1372 samples, 4 real-valued features
* **Features**:

  * Wavelet Transformed Variance
  * Wavelet Transformed Skewness
  * Wavelet Transformed Curtosis
  * Image Entropy
  * Class Label (0 = Forged, 1 = Genuine)

---

## 🧪 Techniques Used

* **SVM Kernels**:

  * Linear
  * Polynomial
  * Radial Basis Function (RBF)
  * Sigmoid
  * Precomputed Kernel
* **Multi-Kernel SVM**:

  * Combines custom implementations of Linear, RBF, and Polynomial kernels with random weighting.

---

## 🧾 Project Structure

| File/Folder                        | Description                                 |
| ---------------------------------- | ------------------------------------------- |
| `data_banknote_authentication.txt` | Raw dataset file                            |
| `notebook.ipynb`                   | Main notebook with code and experimentation |
| `README.md`                        | Project documentation                       |

---

## ⚙️ Installation

Make sure you have Python 3.8+ installed. Then, set up the environment using:

```bash
pip install -r requirements.txt
```

**Required Libraries**:

* `numpy`
* `pandas`
* `scikit-learn`
* `prettytable`
* `math` (standard lib)

You can optionally set up a virtual environment:

```bash
python -m venv env
source env/bin/activate  # or .\env\Scripts\activate on Windows
```

---

## ▶️ Usage

1. **Run the Jupyter Notebook**:

   ```bash
   jupyter notebook
   ```

   Then open the notebook and execute all cells.

2. **Try Different Kernel Settings**:
   Modify the test cases at the end of the notebook to tune hyperparameters like:

   * `C` (Regularization parameter)
   * `degree` (for Polynomial kernel)

3. **View Results**:
   Output is displayed in tabular format using `PrettyTable`.

---

## 📊 Results

Example of accuracy across kernels (with C=0.6, degree=2):

| Kernel       | Accuracy |
| ------------ | -------- |
| Linear       | 99.09%   |
| Polynomial   | 94.72%   |
| RBF          | 99.45%   |
| Sigmoid      | 69.58%   |
| Precomputed  | 99.09%   |
| Multi-Kernel | 98.00%   |

---

## ⚠️ Limitations

* The **Multi-Kernel SVM** uses random weights for kernel combination, which introduces **non-determinism** in results.
* No hyperparameter optimization (like grid search) was applied.
* Currently does not support scaling to large datasets or streaming inputs.

---

## 🚀 Future Improvements

* Add **cross-validation** for model evaluation.
* Optimize kernel weights using algorithms like **semi-definite programming (SDP)** or **gradient descent**.
* Integrate **hyperparameter tuning** (e.g., GridSearchCV).
* Add visualization of decision boundaries using PCA or t-SNE.

---

## 📌 Author

Developed by \Rajendra Kujur as part of an academic project on Banknote Classification using Multi Kernel SVM Learning.

---


