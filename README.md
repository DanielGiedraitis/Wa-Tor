# Concurrent Development Wa-Tor Project

---

Welcome to my Wa-Tor Project folder for my Concurrent Development module.

## Plot Min durations for each thread count:
A bar plot using Matplotlib to display the performance metrics of a parallelized implementation of the "Wa-Tor" simulation with different thread counts. It showcases the minimum duration achieved for different thread counts in executing the simulation.

The purpose of the graph is to visually represent the minimum duration (in milliseconds) taken by the simulation to complete for different thread counts. Each bar represents the minimum duration obtained for a specific thread count. The x-axis denotes the number of threads used, while the y-axis represents the duration in milliseconds.

The graph allows for a comparative analysis of the performance of the simulation concerning different thread counts. Lower durations imply better performance or faster execution times. Thus, this graph helps in assessing the impact of parallelization (using different thread counts) on the simulation's runtime, aiming to determine the most efficient configuration for running the "Wa-Tor" simulation.

![minPlot](https://github.com/DanielGiedraitis/Wa-Tor/assets/91562130/9dd991f8-6d12-4799-b53d-382e14be6127)

---

## Plot Max durations for each thread count:
This bar plot using Matplotlib visualizes the maximum durations achieved during the execution of the "Wa-Tor" simulation with varying thread counts.

Similar to the previous plot, here each bar represents the maximum duration (in milliseconds) obtained for a specific thread count configuration. The x-axis displays the number of threads used, while the y-axis represents the duration in milliseconds. The purpose of this graph is different from the plot displaying minimum durations. It aims to illustrate the maximum time taken for the simulation to complete with different thread counts. Higher durations imply that the simulation took longer to finish its execution.

By visualizing the maximum durations across different thread counts, this graph helps identify scenarios where the simulation might experience spikes or higher execution times. These peaks can be crucial for assessing the simulation's performance under varying computational loads and optimizing the configuration for more consistent or efficient execution.

![maxPlot](https://github.com/DanielGiedraitis/Wa-Tor/assets/91562130/4d9726cc-bb30-42b3-a905-3946b4989aa0)

---

## Plot Avg durations for each thread count:
This bar plot using Matplotlib, specifically shocases the average durations achieved when running the "Wa-Tor" simulation with different thread counts.

Similar to the previous plots, this graph visualizes the average duration (in milliseconds) for each thread count configuration. Each bar represents the average time taken by the simulation to complete its execution for a specific thread count. The x-axis indicates the number of threads utilized, while the y-axis displays the duration in milliseconds.

The primary purpose of this graph is to offer insight into the average performance of the simulation under different threading configurations. Unlike the minimum and maximum duration plots, which respectively represent the best and worst case scenarios in terms of execution time, the average duration plot provides a more balanced view of the simulation's runtime performance across various thread counts.

![averagePlot](https://github.com/DanielGiedraitis/Wa-Tor/assets/91562130/cee789fb-7f79-465b-be02-4a91fb3003ee)

---

## A subplot for Min, Max, and Avg durations in one graph:
A bar plot using Matplotlib to showcase the minimum, maximum, and average durations achieved during the execution of the "Wa-Tor" simulation with varying thread counts.

The purpose of this graph is to offer a comprehensive comparison of the minimum, maximum, and average durations for different thread counts in a single visualization. 

![minMaxAvg](https://github.com/DanielGiedraitis/Wa-Tor/assets/91562130/a9e5a2ae-544d-4473-a90d-10ecc1027552)

---

## Mean durations and standard deviations for each thread count
Using Matplotlib to generate an error line plot, showcasing the mean durations and the variability (standard deviations) in durations observed for the "Wa-Tor" simulation across different thread counts.

The purpose of this error line plot is to visually represent both the average (mean) durations and the variability (standard deviations) associated with these durations across different thread counts. It allows for an understanding of the spread or dispersion of duration values around the mean for each thread count configuration.

![ErrorLine](https://github.com/DanielGiedraitis/Wa-Tor/assets/91562130/e7d17b92-0ba0-4439-8754-de89b04edcb1)

---

## How to install project
To set up this project on your system, follow these steps:

1. Ensure that GCC, SFML, Make, and OpenMP are installed on your machine.
2. Clone this repository to your local environment.
3. Open your terminal and navigate to the project directory.
4. Once in the folder, use the following commands:

    - **Build the Executables:**
        - Run `make` or `make build` to generate the main executables.
        - To create a debug version with symbols:
            - Use `make debug` to build the executables with debug symbols.
        
    - **Run the Executables:**
        - To execute the generated programs, use the shell command `./wator`


## Repository
[GitHub Repository](https://github.com/DanielGiedraitis/Wa-Tor)

## License
[GNU General Public License v3.0 ](https://www.gnu.org/licenses/gpl-3.0.en.html)

## Author
- **Name:** Daniel Giedraitis
- **Email:** daniel.giedraitis@gmail.com
- **Other Projects:** https://github.com/DanielGiedraitis
- **LinkedIn:** https://www.linkedin.com/in/daniel-giedraitis
