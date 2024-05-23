import gymnasium as gym
import numpy as np
import matplotlib.pyplot as plt

MAX_STEPS = 100

def epsilon_greedy(state_index: int, num_actions: int, q_table: np.ndarray, epsilon: float) -> int:
    if np.random.random() <= epsilon:
        return np.random.randint(num_actions)
    return np.argmax(q_table[state_index])

def update_q_table(q_table: np.ndarray, current_state: int, chosen_action: int, new_state: int,
                   new_action: int, reward: float, discount_factor: float, alpha: float) -> np.ndarray:
    td_error = reward + discount_factor * q_table[new_state, new_action] - q_table[current_state, chosen_action]
    q_table[current_state, chosen_action] += alpha * td_error
    return q_table

def run_episode(env: gym.Env, q_table: np.ndarray, epsilon: float, discount_factor: float, alpha: float) -> int:
    current_state = env.reset()[0]
    total_rewards = 0

    for _ in range(MAX_STEPS):
        chosen_action = epsilon_greedy(current_state, env.action_space.n, q_table, epsilon)
        new_state, reward, done, _, _ = env.step(chosen_action)

        if done:
            break

        new_action = epsilon_greedy(new_state, env.action_space.n, q_table, epsilon)
        q_table = update_q_table(q_table, current_state, chosen_action, new_state, new_action, reward, discount_factor, alpha)

        total_rewards += reward
        current_state = new_state

    return total_rewards

num_episodes = 1000
epsilon = 0.1
discount_factor = 0.99
alpha = 0.1
env = gym.make("CliffWalking-v0")

q_learning_rewards = np.zeros(num_episodes)
sarsa_rewards = np.zeros(num_episodes)
runs_averaging = 10

for _ in range(runs_averaging):
    q_table_q_learning = np.zeros((env.observation_space.n, env.action_space.n))
    q_table_sarsa = np.zeros((env.observation_space.n, env.action_space.n))

    for episode in range(num_episodes):
        q_learning_rewards[episode] += run_episode(env, q_table_q_learning, epsilon, discount_factor, alpha)
        sarsa_rewards[episode] += run_episode(env, q_table_sarsa, epsilon, discount_factor, alpha)

q_learning_rewards /= runs_averaging
sarsa_rewards /= runs_averaging

print("Average rewards for Q-learning:")
print(q_learning_rewards)
print("\nAverage rewards for SARSA:")
print(sarsa_rewards)

x_values = np.arange(num_episodes)
plt.plot(x_values, q_learning_rewards, label="Q-learning")
plt.plot(x_values, sarsa_rewards, label="SARSA")
plt.xlabel("Episode")
plt.ylabel("Average Reward")
plt.legend()
plt.title("Average Reward over 1000 Episodes for 10 Runs")
plt.show()
