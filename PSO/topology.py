__author__ = 'tiago'

from math import sqrt

class Topology:

    def __init__(self,swarm,topology):

        self.name   = topology

        if topology == 'mesh':
            self.Mesh(swarm)
        else:
            self.Mesh(swarm)


    def Mesh(self,swarm):

        self.sizeOfNeighboor    = 4
        particle                = swarm.particle
        side                    = int (sqrt(swarm.sizeOfSwarm))

        for i in range(side):
            for j in range(side):

                pos = i*side + j
                particle[pos].SetNeighboor(4)

                if i - 1 < 0:
                    particle[pos].neighbor[0] = (side - 1)*side + j
                else:
                    particle[pos].neighbor[0] = (i-1)*side + j

                if i + 1 > side - 1:
                    particle[pos].neighbor[1] = j
                else:
                    particle[pos].neighbor[1] = (i+1)*side + j

                if pos - 1 < i*side:
                    particle[pos].neighbor[2] = (i+1)*side - 1
                else:
                    particle[pos].neighbor[2] = pos - 1

                if pos + 1 > (i+1)*side - 1:
                    particle[pos].neighbor[3] = i*side
                else:
                    particle[pos].neighbor[3] = pos + 1

