# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util
from game import Directions
# from typing import List


class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem: SearchProblem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    s = Directions.SOUTH
    w = Directions.WEST
    return [s, s, w, s, w, w, s, w]


def depthFirstSearch(problem: SearchProblem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    # print("Start:", problem.getStartState())
    # print("goal-state?", problem.isGoalState(problem.getStartState()))
    # print("State's_successors:", problem.getSuccessors(problem.getStartState()))
    """
    "*** YOUR CODE HERE ***"

    fringe = util.Stack()
    closed = set()
    fringe.push((problem.getStartState(), []))

    while not fringe.isEmpty():
        # print("closed:", closed)
        curr_state, path = fringe.pop()
        # print(f"\ncurrent={curr_state}-> ", end="")
        # print("goal-state?", problem.isGoalState(curr_state))
        # print("State's_successors:", problem.getSuccessors(curr_state))

        if problem.isGoalState(curr_state):
            # print(f"\n\npath:{path}")
            return path

        if curr_state not in closed:
            closed.add(curr_state)
            for succ, direction, _ in problem.getSuccessors(curr_state):
                if succ not in closed:
                    fringe.push((succ, path + [direction]))
    return []


def breadthFirstSearch(problem: SearchProblem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"

    fringe = util.Queue()
    closed = set()
    fringe.push((problem.getStartState(), []))

    while not fringe.isEmpty():
        # print("closed:", closed)
        curr_state, path = fringe.pop()
        # print(f"\ncurrent={curr_state}-> ", end="")
        # print("goal-state?", problem.isGoalState(curr_state))
        # print("State's_successors:", problem.getSuccessors(curr_state))

        if problem.isGoalState(curr_state):
            # print(f"\n\npath:{path}")
            return path

        if curr_state not in closed:
            closed.add(curr_state)
            for succ, direction, _ in problem.getSuccessors(curr_state):
                if succ not in closed:
                    fringe.push((succ, path + [direction]))
    return []


def uniformCostSearch(problem: SearchProblem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"

    fringe = util.PriorityQueue()
    closed = dict()
    start = problem.getStartState()
    fringe.push((start, [], 0), 0)

    while not fringe.isEmpty():
        # print("closed:", closed)
        curr_state, path, cost = fringe.pop()
        # print(f"\ncurrent={curr_state}-> ", end="")
        # print("goal-state?", problem.isGoalState(curr_state))
        # print("State's_successors:", problem.getSuccessors(curr_state))

        if problem.isGoalState(curr_state):
            # print(f"\n\npath:{path}")
            return path

        if curr_state not in closed or cost < closed[curr_state]:
            closed[curr_state] = cost
            for succ, direction, step_cost in problem.getSuccessors(curr_state):
                total = cost + step_cost
                if succ not in closed or total < closed[succ]:
                    fringe.push((succ, path + [direction], total), total)
    return []


def nullHeuristic(state, problem=None) -> float:
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0


def aStarSearch(problem: SearchProblem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"

    fringe = util.PriorityQueue()
    closed = dict()
    start = problem.getStartState()
    fringe.push((start, [], 0), heuristic(start, problem))

    while not fringe.isEmpty():
        # print("closed:", closed)
        curr_state, path, cost = fringe.pop()
        # print(f"\ncurrent={curr_state}-> ", end="")
        # print("goal-state?", problem.isGoalState(curr_state))
        # print("State's_successors:", problem.getSuccessors(curr_state))

        if problem.isGoalState(curr_state):
            # print(f"\n\npath:{path}")
            return path

        if curr_state not in closed or cost < closed[curr_state]:
            closed[curr_state] = cost
            for succ, direction, step_cost in problem.getSuccessors(curr_state):
                g_cost = cost + step_cost
                if succ not in closed or g_cost < closed[succ]:
                    h_cost = heuristic(succ, problem)
                    fringe.push((succ, path + [direction], g_cost), g_cost + h_cost)
    return []


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
