__author__ = 'tiago'

import numpy as np
from topology import Topology
INF = 2147483647.0

class Swarm:

    def __init__(self,sizeOfSwarm,sizeOfDimension,h_num,l_num,topology):

        self.sizeOfDimension    = sizeOfDimension
        self.sizeOfSwarm        = sizeOfSwarm
        self.highestNumber      = h_num
        self.lowestNumber       = l_num
        self.weight             = 0
        self.particle           = []

        self.DefaultParameter()
        self.InicializeParticles()

        self.topology           = Topology(self,topology)


    def InicializeParticles(self):

        sizeOfSwarm = self.sizeOfSwarm
        particle    = self.particle

        for i in range(sizeOfSwarm):
            particle.append(Particle(self))

    def DefaultParameter(self):

        self.accelaration1      = 2
        self.accelaration2      = 2
        self.maxInteraction     = 300
        self.minWeight          = 0.4
        self.maxWeight          = 0.5

    def EspecifyParameter(self,acc1,acc2,maxInteraction,minWeight,maxWeight):

        self.accelaration1      = acc1
        self.accelaration2      = acc2
        self.maxInteraction     = maxInteraction
        self.minWeight          = minWeight
        self.maxWeight          = maxWeight - minWeight


class Particle:

    def __init__(self,swarm):

        l_num = swarm.lowestNumber
        h_num = swarm.highestNumber

        self.currentFitness     = 0.0
        self.bestFitness        = INF
        self.localFitness       = INF
        self.velocity           = np.zeros(swarm.sizeOfDimension,np.float64)
        self.bestPosition       = np.zeros(swarm.sizeOfDimension,np.float64)
        self.localPosition      = np.zeros(swarm.sizeOfDimension,np.float64)
        self.currentPosition    = np.random.rand(swarm.sizeOfDimension)

        self.currentPosition = self.currentPosition*(h_num-l_num) + l_num

    def SetNeighboor(self,sizeOfNeighboor):

        self.neighbor = np.zeros(sizeOfNeighboor,np.int32)





