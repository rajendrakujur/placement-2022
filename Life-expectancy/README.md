# 📊 Statistical Analysis on Factors Influencing Life Expectancy (2022)

This project explores the key health, education, and economic factors influencing global life expectancy using WHO and UN data. Built in R, the analysis includes data preprocessing, correlation study, and regression modeling.

---

## 📌 Project Overview

- **Goal:** Identify the main predictors of life expectancy across countries
- **Dataset:** WHO Global Health Observatory (GHO), United Nations
- **Tools:** R programming, `ggplot2`, OLS Regression
- **Data Size:** 1,649 records × 22 features (post-cleaning)
- **Focus Year:** 2022

---

## 🧠 Problem Statement

- Should countries with lower life expectancy invest more in healthcare?
- How do mortality, education, and income levels influence life expectancy?
- Do lifestyle choices (alcohol, BMI, etc.) significantly affect longevity?

---

## 🧮 Data Summary

- **Original Size:** 2,938 rows × 22 columns  
- **Cleaned Size:** 1,649 rows (after removing null and invalid entries)
- **Target Variable:** `LifeExpectancy`
- **Key Features:**  
  `AdultMortality`, `InfantDeaths`, `HIV/AIDS`, `Alcohol`, `BMI`,  
  `Schooling`, `IncomeCompositionOfResources`, `GDP`, `Population`,  
  `Status`, `Country`

---

## ⚙️ Preprocessing Steps

- Dropped rows with excessive missing values (44% data reduction)
- Encoded categorical variables:
  - `Status`: 0 = Developing, 1 = Developed
  - `Country`: Numerically encoded
- Standardized feature names for consistency

---

## 📈 Exploratory Data Analysis

- Generated correlation matrix and scatterplots using `ggplot2`
- Identified variables most and least correlated with life expectancy

### 🔍 Top Correlations

| Feature                    | Correlation | Interpretation               |
|----------------------------|-------------|-------------------------------|
| Income Composition         | +0.79       | Strong positive correlation   |
| Schooling                  | +0.75       | Strong positive correlation   |
| Adult Mortality            | –0.69       | Strong negative correlation   |
| HIV/AIDS                   | –0.56       | Strong negative correlation   |
| BMI                        | +0.52       | Moderate positive correlation |

---

## 📊 Regression Modeling

- **Model Used:** Ordinary Least Squares (OLS)
- **Selected Features:**  
  `AdultMortality`, `IncomeCompositionOfResources`, `Schooling`, `HIV/AIDS`, `BMI`

### Final Regression Equation

```
Life Expectancy = 52.28
- 0.01 × Adult Mortality
+ 12.24 × Income
+ 0.97 × Schooling
- 0.52 × HIV/AIDS
+ 0.03 × BMI
```

- **R²:** 0.825  
- **Adjusted R²:** 0.824

---

## 📉 Residual Diagnostics

- Residual and Q-Q plots used to assess model assumptions
- No major violations observed
- Multicollinearity check (e.g., VIF) not performed during project phase

---

## ✅ Key Insights

- **Positive Predictors:** Income, Schooling, BMI
- **Negative Predictors:** Adult Mortality, HIV/AIDS
- **Insignificant Factors:** Alcohol consumption, Population density

---

## 🏁 Conclusion

Improved education and income distribution are strong drivers of increased life expectancy. Countries with high adult mortality and HIV/AIDS prevalence see the sharpest declines. The model suggests that addressing core health and education issues may yield better outcomes than solely increasing healthcare expenditure.

---

## 🚀 Future Work

- Add multicollinearity checks (e.g., VIF)
- Include regional segmentation (continent-wise models)
- Introduce advanced regression (e.g., Ridge, Lasso)
- Deploy interactive visualizations via Shiny app

---

## 📂 Project Structure

```
life_expectancy_analysis/
│
├── data/
│   └── life_expectancy_cleaned.csv
├── scripts/
│   └── analysis.R
├── plots/
│   └── correlation_matrix.png
│   └── regression_diagnostics.png
├── README.md
└── life_expectancy_report.pdf
```

---

## 📎 References

- WHO Global Health Observatory  
- United Nations Economic Indicators  
- ggplot2 Documentation  
- R Base Regression: `lm()` Function
