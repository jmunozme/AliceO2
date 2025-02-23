// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// @file   TrackerSpec.h

#ifndef O2_ITS_TRACKERDPL
#define O2_ITS_TRACKERDPL

#include "DataFormatsParameters/GRPObject.h"
#include "DataFormatsITSMFT/TopologyDictionary.h"
#include "DataFormatsCalibration/MeanVertexObject.h"

#include "Framework/DataProcessorSpec.h"
#include "Framework/Task.h"

#include "ITStracking/TrackingInterface.h"

#include "GPUDataTypes.h"
#include "DetectorsBase/GRPGeomHelper.h"

#include "TStopwatch.h"

namespace o2
{
namespace its
{

class TrackerDPL : public framework::Task
{
 public:
  TrackerDPL(std::shared_ptr<o2::base::GRPGeomRequest> gr,
             bool isMC,
             int trgType,
             const TrackingMode& trMode = TrackingMode::Unset,
             const bool overrBeamEst = false,
             gpu::GPUDataTypes::DeviceType dType = gpu::GPUDataTypes::DeviceType::CPU);
  ~TrackerDPL() override = default;
  void init(framework::InitContext& ic) final;
  void run(framework::ProcessingContext& pc) final;
  void endOfStream(framework::EndOfStreamContext& ec) final;
  void finaliseCCDB(framework::ConcreteDataMatcher& matcher, void* obj) final;
  void stop() final;

 private:
  void updateTimeDependentParams(framework::ProcessingContext& pc);
  std::unique_ptr<o2::gpu::GPUReconstruction> mRecChain = nullptr;
  std::unique_ptr<o2::gpu::GPUChainITS> mChainITS = nullptr;
  std::shared_ptr<o2::base::GRPGeomRequest> mGGCCDBRequest;
  ITSTrackingInterface mITSTrackingInterface;
  TStopwatch mTimer;
};

using o2::its::TrackingMode;
framework::DataProcessorSpec getTrackerSpec(bool useMC, bool useGeom, int useTrig, const std::string& trMode, const bool overrBeamEst = false, gpu::GPUDataTypes::DeviceType dType = gpu::GPUDataTypes::DeviceType::CPU);

} // namespace its
} // namespace o2

#endif /* O2_ITS_TRACKERDPL */
