from random import random
from dataclasses import dataclass

import numpy as np

@dataclass
class State:
    generation = 0
    handling = 1


@dataclass
class Constants:
    time = 0
    state = 1

class QSystem:
    def __init__(self, a, b, mu, sigma, n, p, t):
        self.a = a
        self.b = b
        self.mu = mu
        self.sigma = sigma
        self.n = n
        self.p = p
        self.t = t

        self.generator_state = False
        self.handler_state = False

    def step_principle(self):
        max_length = 0
        now_length = 0
        processed_msgs = 0
        self.handler_state = False

        now_time = self.t
        generation_time = np.random.uniform(self.a, self.b)
        prev_generation_time = 0
        handling_time = 0

        while processed_msgs < self.n:

            if now_time > generation_time:
                now_length += 1

                if max_length < now_length:
                    max_length = now_length

                prev_generation_time = generation_time
                generation_time += np.random.uniform(self.a, self.b)

            if now_time > handling_time:
                if now_length > 0:
                    was_free = self.handler_state

                    if not self.handler_state:
                        self.handler_state = True
                    else:
                        processed_msgs += 1
                        now_length -= 1

                        now_return_probability = random()

                        if now_return_probability <= self.p:
                            now_length += 1

                    if not was_free:
                        handling_time = prev_generation_time + \
                                        np.random.normal(self.mu, self.sigma)
                    else:
                        handling_time += np.random.normal(self.mu, self.sigma)

                else:
                    self.handler_state = False

            now_time += self.t

        return max_length

    def event_principle(self):
        max_length = 0
        now_length = 0
        processed_msgs = 0
        processed = False
        self.handler_state = False

        events = [[np.random.uniform(self.a, self.b), State.generation]]

        while processed_msgs < self.n:
            event = events.pop(0)

            if event[Constants.state] == State.generation:
                now_length += 1

                if max_length < now_length:
                    max_length = now_length

                self.__add_event(events, [event[Constants.time] + np.random.uniform(self.a, self.b),
                                          State.generation])

                if not self.handler_state:
                    processed = True

            if event[Constants.state] == State.handling:
                processed_msgs += 1
                now_return_probability = random()

                if now_return_probability <= self.p:
                    now_length += 1

                processed = True

            if processed:
                if now_length > 0:
                    now_length -= 1
                    self.__add_event(events, [event[Constants.time] + \
                                              np.random.normal(self.mu, self.sigma),
                                              State.handling])
                    self.handler_state = True
                else:
                    self.handler_state = False

                processed = False

        return max_length

    def __add_event(self, events, event):
        i = 0

        while i < len(events) and \
                events[i][Constants.time] < event[Constants.time]:
            i += 1

        if 0 < i < len(events):
            events.insert(i - 1, event)
        else:
            events.insert(i, event)