# IR2117 - Robot Programming and Simulation

This repository includes a set of hands-on exercises developed during the **IR2117 - Robot Programming and Simulation** course, part of the 2nd year of the **Bachelor's Degree in Robotic Intelligence** at **Universitat Jaume I**.

The course introduces the essential building blocks of robot middleware and simulation, with a focus on the **Robot Operating System (ROS1)** and tools such as **Gazebo**, **Webots**, and **Turtlesim**.

---

## 🛠️ Tools & Technologies

- 🐢 **ROS 1 (Noetic)**
- 🌍 **Gazebo**
- 🧪 **Webots**
- 🎨 **Turtlesim**
- 💻 **C++ / Python**

---

## 🎯 Learning Outcomes

- Controlling mobile robots and planning their movements
- Time-based control and parameterized behaviors
- Detecting and avoiding obstacles
- Designing ROS services and custom action servers
- Using simulated environments to verify and test robot logic
- Combining manual and autonomous control methods

---

## 🧪 Key Exercises

### 1. 🔲 Square Trajectory Execution  
Implemented a robot that follows a square path using:

- **Turtlesim** and **Gazebo**
- Movement controlled via time or ROS parameters
- Parameterized and basic implementations included

---

### 2. 🚶‍♂️ Wandering Behavior  
Created a reactive wandering robot using:

- Obstacle detection sensors in **Gazebo** and **Webots**
- A launch file for simplified setup across simulators
- Simulated **TurtleBot3** navigating autonomously and avoiding collisions

---

### 3. 🧱 Obstacle Detection & Avoidance  
Developed a behavior where the robot continuously:

- Detects obstacles ahead using simulated range data (e.g., laser/IR)
- Adjusts its trajectory to navigate around them
- Switches between free roaming and reactive control
- Tested across **Gazebo** and **Webots** environments

---

### 4. 🟡 Drawing Olympic Rings – ROS Services  
Built a service-based drawing robot that renders the Olympic rings in **Turtlesim**:

- Used custom ROS services for movement and color control
- Controlled ring size and position with ROS parameters
- Called standard services: `setpen`, `teleport_absolute`, `teleport_relative`
- Executed five colored circles using a loop structure

---

### 5. 🟢 Drawing Olympic Rings – ROS Actions  
Extended the previous project using ROS Actions:

- Defined a custom action in the `olympic_interfaces` package
- Developed both action server and client nodes
- Included real-time progress updates and success confirmation
- Reused ring-drawing logic in a more modular, feedback-oriented structure

---

## 🛡️ Skills Acquired

- Solid understanding of ROS architecture: nodes, topics, services, actions
- Designed modular and maintainable ROS packages
- Simulated and tested autonomous robot behaviors
- Applied real-time control and state feedback in robot applications
- Practiced integrating middleware with virtual testing environments

---

Explore each folder for source code, launch files, and simulator configurations for each exercise.
