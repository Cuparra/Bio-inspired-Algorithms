__author__ = 'tiago'

from swarm import Swarm, np
from pso import*

n = 2

def ackley(x):
    
    arg1 = np.sum( -0.2 * np.sqrt( (1/n) * ( x**2) ), axis = 1 )

    arg2 = (1/n) *( np.sum( np.cos(2.0*np.pi*x), axis = 1)  )

    return -20. * np.exp(arg1) - np.exp(arg2) + 20. + np.e

def main():

    swarm = Swarm(81, n, 5,-5,'mesh')
    pso   = PSO(swarm,P.Function)
    pso.Optmize()

    x = swarm.particle.bestPosition


if __name__ == "__main__": main()