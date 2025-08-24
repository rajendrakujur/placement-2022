# 🚀 PostCom2DR – Rumor Detection on Twitter Using Post-Comment Graph Networks (2022)

This project focuses on detecting misinformation on Twitter by leveraging both textual content and conversation dynamics. The model analyzes tweets along with their reply structures to identify rumors using graph-based deep learning.

---

## 📌 Project Overview

* **Objective:** Detect rumors on Twitter by modeling both content and reply-chain structures.
* **Approach:** Graph-based deep learning using Graph Convolutional Networks (GCNs) and self-attention.
* **Data Source:** Twitter posts and replies (\~9GB raw data), collected during research for academic purposes.
* **Tools & Technologies:** Python, PyTorch, NetworkX, Pandas, NumPy.

---

## 🧠 Problem Statement

* Traditional rumor detection focuses on individual tweets, ignoring the context of replies and conversation flow.
* Misinformation often spreads through structured reply threads rather than single messages.
* The challenge was to design a model capable of capturing both **textual and relational features** for accurate rumor identification.

---

## ⚙️ Methodology & Approach

1. **Data Engineering**

   * Cleaned and validated over 9GB of raw Twitter data.
   * Constructed conversation graphs where tweets are nodes and replies are edges.
   * Preprocessed text for model input (removing noise, tokenization, embedding preparation).

2. **Model Design**

   * Implemented a **two-layer Graph Convolutional Network (GCN)** to learn relational features.
   * Integrated a **self-attention mechanism** to weigh influential replies more heavily.
   * Combined textual embeddings with graph embeddings to form a dual-representation model.

3. **Training & Evaluation**

   * Trained the model on labeled data for rumor vs. non-rumor classification.
   * Compared performance against baseline text-only models.
   * Evaluated accuracy and contextual understanding of the conversation graph.

---

## 📊 Key Concepts & Insights

* **Graph Representation:** Tweets and replies are represented as nodes and edges to model propagation.
* **Contextual Feature Learning:** GCNs capture structural relationships, while self-attention captures relative importance of replies.
* **Scalability:** Batch processing and efficient PyTorch pipelines allowed handling large datasets on limited resources.
* **Applications:** This approach demonstrates potential in **financial sentiment analysis, brand reputation monitoring, and digital risk management**.

---

## 🌐 Potential Business & Finance Applications

* **Market Sentiment Analysis:** Early detection of false news can prevent panic trading or portfolio mismanagement.
* **Reputation Management:** Companies can monitor rumors affecting executives, products, or services.
* **Regulatory Compliance:** Identifying misinformation helps ensure ESG reporting and MiFID II compliance.
* **Crisis Management:** Detecting false narratives during earnings calls, product launches, or geopolitical events.

---

## 📂 Project Structure

```
PostCom2DR/
│
├── data/
│   └── twitter_raw_data.csv
├── scripts/
│   └── preprocessing.py
│   └── train_model.py
├── models/
│   └── gcn_attention_model.pth
├── notebooks/
│   └── exploratory_analysis.ipynb
├── README.md
└── report.pdf
```

---

## 📎 References

* Research papers on **rumor detection using GCNs and graph attention networks**.
* PyTorch and NetworkX documentation.
* Twitter API documentation for data collection.
