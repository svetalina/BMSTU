from Modeller import Modeller
from EventGenerator import Generator
from Distributions import  RayleighDistribution
from Processor import Processor
import math
from matplotlib import pyplot

def modelling(clients_number, clients_proccessed, lambda_coming, lambda_obr): 
    sigma_coming = (1/lambda_coming) * (math.pi / 2) ** (-1/2)
    sigma_obr = (1 / lambda_obr) * (math.pi / 2) ** (-1 / 2)

    generators = [
        Generator(
            RayleighDistribution(sigma_coming),
            clients_number,
        ),]

    operators = [
            Processor(
                RayleighDistribution(sigma_obr),
            ),]

    for generator in generators: 
        generator.receivers = operators.copy()

    model = Modeller(generators, operators)
    result = model.event_mode(clients_proccessed)
    return result


def view(start, end, step, N, Exps, lambda_com, lambda_obr):
    Xdata1 = list()
    Ydata1 = list()

    for lambda_coming in range(int(start * 100), int(end * 100), int(step * 100)):
        print("lambda_coming = {}".format(lambda_coming))
        wait_time_middles = []
        for _ in range(int(Exps)):
            result = modelling(
                clients_number=N+1000,
                clients_proccessed=N,
                lambda_coming=lambda_coming,
                lambda_obr=lambda_obr
            )
            wait_time_middles.append(result['wait_time_middle'])

        Xdata1.append(lambda_coming/lambda_obr)
        Ydata1.append(sum(wait_time_middles) / len(wait_time_middles))

    pyplot.figure()
    pyplot.title('Среднее время ожидания')
    pyplot.grid(True)
    pyplot.plot(Xdata1, Ydata1)
    pyplot.xlabel("Загрузка СМО")
    pyplot.ylabel("Среднее время пребывания в очереди")

    Xdata2 = list()
    Ydata2 = list()

    for lambda_o in range(int(start * 100), int(end * 100), int(step * 100)):
        print("lambda_o = {}".format(lambda_o))
        wait_time_middles = []
        for _ in range(int(Exps)):
            result = modelling(
                clients_number=N+1000,
                clients_proccessed=N,
                lambda_coming=lambda_o,
                lambda_obr=lambda_obr
            )
            wait_time_middles.append(result['wait_time_middle'])

        Xdata2.append(lambda_o)
        Ydata2.append(sum(wait_time_middles) / len(wait_time_middles))

    pyplot.figure()
    pyplot.title('Среднее время ожидания')
    pyplot.grid(True)
    pyplot.plot(Xdata2, Ydata2)
    pyplot.xlabel("Интенсивность поступления заявок")
    pyplot.ylabel("Среднее время пребывания в очереди")

    Xdata3 = list()
    Ydata3 = list()

    for lambda_o in range(int(start * 100), int(end * 100), int(step * 100)):
        print("lambda_o = {}".format(lambda_o))
        wait_time_middles = []
        for _ in range(int(Exps)):
            result = modelling(
                clients_number=N+1000,
                clients_proccessed=N,
                lambda_coming=lambda_com,
                lambda_obr=lambda_o
            )
            wait_time_middles.append(result['wait_time_middle'])

        Xdata3.append(lambda_o)
        Ydata3.append(sum(wait_time_middles) / len(wait_time_middles))

    pyplot.figure()
    pyplot.title('Среднее время ожидания')
    pyplot.grid(True)
    pyplot.plot(Xdata3, Ydata3)
    pyplot.xlabel("Интенсивность обслуживания заявок")
    pyplot.ylabel("Среднее время пребывания в очереди")

    pyplot.show()