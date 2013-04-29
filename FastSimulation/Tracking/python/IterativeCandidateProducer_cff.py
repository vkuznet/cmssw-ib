import FWCore.ParameterSet.Config as cms

from FastSimulation.Tracking.IterativeFirstCandidateProducer_cff import *
from FastSimulation.Tracking.IterativeSecondCandidateProducer_cff import *
from FastSimulation.Tracking.IterativeThirdCandidateProducer_cff import *
iterativeTrackCandidates = cms.Sequence(iterativeFirstTrackCandidates+iterativeSecondTrackCandidates+iterativeThirdTrackCandidates)

