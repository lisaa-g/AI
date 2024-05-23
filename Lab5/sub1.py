def HMM(observations):
    #prior probabilities
    rain_prob = 0.5
    no_rain_prob = 0.5

    #transition probabilities
    transition_probs = {
        'rain_to_rain': 0.7,
        'rain_to_no_rain': 0.3,
        'no_rain_to_rain': 0.3,
        'no_rain_to_no_rain': 0.7
    }

    #emission probabilities
    emission_probs = {
        'umbrella_given_rain': 0.9,
        'umbrella_given_no_rain': 0.2
    }

    probabilities = [(rain_prob, no_rain_prob)]
    for obs in observations:
        rain_prob_next = (probabilities[-1][0] * transition_probs['rain_to_rain'] * emission_probs['umbrella_given_rain'] if obs == 1 else probabilities[-1][0] * transition_probs['rain_to_rain'] * (1 - emission_probs['umbrella_given_rain'])) + \
                         (probabilities[-1][1] * transition_probs['no_rain_to_rain'] * emission_probs['umbrella_given_rain'] if obs == 1 else probabilities[-1][1] * transition_probs['no_rain_to_rain'] * (1 - emission_probs['umbrella_given_rain']))

        no_rain_prob_next = (probabilities[-1][0] * transition_probs['rain_to_no_rain'] * emission_probs['umbrella_given_no_rain'] if obs == 1 else probabilities[-1][0] * transition_probs['rain_to_no_rain'] * (1 - emission_probs['umbrella_given_no_rain'])) + \
                            (probabilities[-1][1] * transition_probs['no_rain_to_no_rain'] * emission_probs['umbrella_given_no_rain'] if obs == 1 else probabilities[-1][1] * transition_probs['no_rain_to_no_rain'] * (1 - emission_probs['umbrella_given_no_rain']))

        total_prob = rain_prob_next + no_rain_prob_next
        rain_prob_next /= total_prob
        no_rain_prob_next /= total_prob
        probabilities.append((rain_prob_next, no_rain_prob_next))

    return probabilities

def print_results(probabilities):
    for i, prob in enumerate(probabilities):
        rounded_prob = round(prob[0], 3)
        print(f"Timestep {i}: {rounded_prob}")




user_input = input()
observations = list(map(int, user_input.split()))
probabilities = HMM(observations)
print_results(probabilities)
