# 🚀 Project: PostCom2DR – Rumor Detection on Twitter Using Post-Comment Graph Networks (2022)

---

## ✅ STAR Framework (Interview Explanation)

**S – Situation**  
During my academic coursework on *Social Media and Data Mining*, I worked with a team of three on a project focused on detecting misinformation on Twitter. The rise of fake news and social manipulation online created an urgent need for intelligent detection models that consider not just content but also conversation dynamics.

**T – Task**  
Our goal was to build a model that could accurately identify rumors by analyzing both the original tweet and the structure of the replies or comments. Unlike single-layer classifiers, we were asked to design a model that uses advanced deep learning and network-based analysis to understand context.

**A – Action**  
We developed **PostCom2DR**, a dual-representation model combining a **two-layer Graph Convolutional Network (GCN)** with a **self-attention mechanism**. The model learned both textual and relational features from the tweet and its reply tree. I led the **data engineering pipeline**, cleaning and validating over **9GB of raw Twitter data**, while also collaborating on model architecture in **PyTorch**. Despite limited academic timeframes, we successfully implemented an optimized structure for contextual rumor detection.

**R – Result**  
The final model demonstrated **improved rumor detection accuracy** compared to baseline methods by leveraging the conversational graph. It showed the potential of combining graph structures with attention to identify misinformation in a scalable way. The project not only enhanced my technical depth but also deepened my understanding of real-time risk signals on social media — directly applicable to finance, crisis management, and digital reputation monitoring.

---

## 🎯 Interview Questions & Suggested Answers

### 1. What was the core objective of this project?
The primary goal was to design a system that detects rumors on Twitter by analyzing both the original post and the structure of replies. Traditional models treat tweets as isolated text units, but we wanted to incorporate how conversations unfold around them. We built a model that uses a graph-based approach to understand the contextual flow of information, making it more robust in detecting misinformation patterns.

### 2. Why did you use GCNs and self-attention in your architecture?
Graph Convolutional Networks were ideal for this task because social media discussions form natural graph structures — with tweets as nodes and replies as edges. GCNs enabled the model to capture the propagation behavior of information. We added self-attention to dynamically weigh the importance of replies in influencing the perception of the original post. This made the model more context-aware and better at identifying subtle patterns of misinformation.

### 3. How did you handle the data complexity and volume?
We worked with a dataset over 9GB in size, which posed real challenges in terms of memory and processing. I took responsibility for designing a scalable preprocessing pipeline that included data validation, null filtering, and content cleaning. To maintain consistency, I applied batch processing and efficient data handling in PyTorch. We didn't have cloud resources, so I optimized workflows to run locally within academic constraints.

### 4. How is this project relevant to business or finance?
False information about companies, executives, or geopolitical events can impact stock prices within minutes. Models like PostCom2DR can be adapted to monitor, detect, and flag such misinformation early. Hedge funds and market makers can use it for *real-time sentiment risk control*, while PR teams can use it for *reputation management*. The underlying tech can support *regulatory compliance* (e.g., MiFID II, ESG claims) by identifying misleading claims affecting financial stakeholders.

### 5. What challenges did you personally face and how did you manage them?
One of the biggest challenges was balancing the technical depth of the project with the academic deadlines. The data volume, combined with the complexity of graph-based models, was initially overwhelming. I focused on structuring the preprocessing workflow early on, ensuring clean and structured input to the model. I also contributed to refining the model’s architecture for better scalability. Beyond the technical aspects, I improved my project planning, team communication, and stress management.

### 6. Was the model evaluated or deployed? How did it perform?
Although the project was academic, we evaluated our model against traditional classifiers and observed improved accuracy and contextual understanding. While I don't recall exact metrics, the integration of graph-based learning with attention mechanisms clearly enhanced the model’s sensitivity to misinformation. If scaled, such a model could be deployed for live monitoring on platforms like Twitter.

### 7. What was your specific contribution to the model?
I played a leading role in handling the end-to-end data pipeline — managing over 9GB of raw data to transform it into usable format. I also contributed to designing the GCN layers, integrating self-attention, and validating the structure of the conversation graphs. This mix of technical execution and architectural design helped me sharpen my AI development skills, especially for unstructured social data.

---

## 📊 Business & Finance Relevance

This project directly applies to several critical areas in business and finance:

* **Market Sentiment Monitoring** – Asset managers and traders rely on social signals to inform decisions. Detecting false narratives early prevents panic trades or poor portfolio moves.  
* **Reputation Risk Mitigation** – Financial firms and brands can monitor misinformation to reduce reputational damage and align with ESG and compliance requirements.  
* **Regulatory Compliance & Digital Auditing** – The ability to trace and detect false claims online can serve as a proactive measure for compliance and reporting (e.g., SEC investigations).  
* **Crisis Management & PR Strategy** – Early detection allows businesses to respond swiftly to disinformation campaigns, especially around earnings calls, product launches, or M&A rumors.  

In an increasingly information-driven financial ecosystem, being able to leverage machine learning to extract insights and control risk from digital conversations is a competitive advantage.

---
