__author__ = 'tiago'

from random import uniform
from swarm import np

NOTCHANGED = -1

class PSO:

    def __init__(self,swarm,function):

        self.time           = 0
        self.swarm          = swarm
        self.function       = function
        self.maxInteraction = swarm.maxInteraction

    def Optmize(self):

        iteraction      = -1
        swarm           = self.swarm
        minWeight       = swarm.minWeight
        maxWeight       = swarm.maxWeight
        maxInteraction  = swarm.maxInteraction
        particle        = swarm.particle

        while self.TerminationCriteria():

            #*Set the fitness of all particles*/
            self.EvaluateParticles(particle)

            #*Set particle's best position*/
            self.SetParticleBestPosition(swarm)

            #Set the neighborhood(local) best position */
            self.SetNeighborhoodBestPosition(swarm)

            #Update the velocity and position of all particles*/
            self.UpdateParticles(swarm)

            #Update weight*/
            iteraction += 1
            swarm.weight = maxWeight*( 1.0*(maxInteraction - iteraction)/maxInteraction ) + minWeight

        print self.FindMinimium(swarm)


    def UpdateParticles(self,swarm):

        w               = swarm.weight
        particle        = swarm.particle
        sizeOfSwarm     = swarm.sizeOfSwarm
        l_num           = swarm.lowestNumber
        acc1            = swarm.accelaration1
        acc2            = swarm.accelaration2
        h_num           = swarm.highestNumber
        sizeOfDimension = swarm.sizeOfDimension
        lenght          = h_num - l_num + 1

        for i in range(sizeOfSwarm):

            velocity    = particle[i].velocity
            curr        = particle[i].currentPosition
            best        = particle[i].bestPosition
            local       = particle[i].localPosition

            r1 = np.random.rand(sizeOfDimension)
            r2 = np.random.rand(sizeOfDimension)

            velocity = w*velocity + acc1*r1*(best - curr) + acc2*r2*(local - curr)
            curr     += velocity



    def SetParticleBestPosition(self,swarm):

        particle        = swarm.particle
        sizeOfDimension = swarm.sizeOfDimension
        sizeOfswarm     = swarm.sizeOfSwarm

        for i in range(sizeOfswarm):

                if particle[i].currentFitness < particle[i].bestFitness:

                    particle[i].bestFitness = particle[i].currentFitness
                    particle[i].bestPosition = 0 + particle[i].currentPosition


    def SetNeighborhoodBestPosition(self,swarm):

        particle        = swarm.particle
        sizeOfNeighbor  = swarm.topology.sizeOfNeighboor
        sizeOfSwarm     = swarm.sizeOfSwarm

        for i in range(sizeOfSwarm):

            best         = particle[i].localFitness
            bestNeighbor = NOTCHANGED

            for j in range(sizeOfNeighbor):

                id = particle[i].neighbor[j]

                if best > particle[id].bestFitness:

                    bestNeighbor = id
                    best         = particle[id].bestFitness


            if bestNeighbor != NOTCHANGED:
                particle[i].localFitness  = best
                particle[i].localPosition = particle[bestNeighbor].bestPosition


    def EvaluateParticles(self,particle):

        function        = self.function
        sizeOfSwarm     = self.swarm.sizeOfSwarm
        sizeOfDimension = self.swarm.sizeOfDimension

        for i in range(sizeOfSwarm):
            function(particle[i].currentPosition , sizeOfDimension)


    def TerminationCriteria(self):

        self.time += 1

        if self.time < self.maxInteraction:
            return True

        return False

    def FindMinimium(self,swarm):

        particle    = swarm.particle
        sizeOfSwarm = swarm.sizeOfSwarm
        minimum     = particle[0].bestFitness

        for i in range(1,sizeOfSwarm):

            if minimum > particle[i].bestFitness:
                minimum = particle[i].bestFitness

        return minimum