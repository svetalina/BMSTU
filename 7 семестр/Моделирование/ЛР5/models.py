from random import random

class EvenDistribution:
    def __init__(self, a: float, b: float):
        self.a = a
        self.b = b

    def generate(self):
        return self.a + (self.b - self.a) * random()

class Generator:
    def __init__(self, distribution, countClients):
        self.distribution = distribution
        self.receivers = []
        self.numbRequests = countClients
        self.next = 0

    def nextTime(self):
        return self.distribution.generate()

    def generateRequest(self):
        self.numbRequests -= 1

        for receiver in self.receivers:
            if receiver.receiveRequest():
                return receiver


class Processor(Generator):
    def __init__(self, distribution, maxQueue):
        self.distribution = distribution
        self.maxQueueSize = maxQueue
        self.currentQueueSize = 0
        self.processedRequests = 0
        self.receivedRequests = 0
        self.next = 0

    def processRequest(self):
        if self.currentQueueSize > 0:
            self.processedRequests += 1
            self.currentQueueSize -= 1

    def receiveRequest(self):
        if self.maxQueueSize == -1 or self.maxQueueSize > self.currentQueueSize:
            self.currentQueueSize += 1
            self.receivedRequests += 1
            return True
        else:
            return False

    def nextTime(self):
        return self.distribution.generate()

class EventModel:
    def __init__(self, generator, operators, computers):
        self.generator = generator
        self.operators = operators
        self.computers = computers

    def run(self):
        refusals = 0
        processed = 0
        generatedRequests = self.generator.numbRequests
        generator = self.generator

        generator.receivers = self.operators.copy()
        self.operators[0].receivers = [self.computers[0]]
        self.operators[1].receivers = [self.computers[0]]
        self.operators[2].receivers = [self.computers[1]]

        generator.next = generator.nextTime()
        self.operators[0].next = self.operators[0].nextTime()

        blocks = [
            generator,
            self.operators[0], self.operators[1], self.operators[2],
            self.computers[0], self.computers[1]
        ]

        while generator.numbRequests >= 0:
            currentTime = generator.next
            for block in blocks:
                if 0 < block.next < currentTime:
                    currentTime = block.next

            for block in blocks:
                if currentTime == block.next:
                    if not isinstance(block, Processor):
                        nextGenerator = generator.generateRequest()
                        if nextGenerator is not None:
                            nextGenerator.next = currentTime + nextGenerator.nextTime()
                            processed += 1
                        else:
                            refusals += 1

                        generator.next = currentTime + generator.nextTime()
                    else:
                        block.processRequest()
                        if block.currentQueueSize == 0:
                            block.next = 0
                        else:
                            block.next = currentTime + block.nextTime()

        return [processed, refusals, refusals / generatedRequests * 100]