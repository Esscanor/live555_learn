// A 'ServerMediaSubsession' object that creates new, unicast, "RTPSink"s
// on demand, from a file.
// C++ header

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#define _FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _ON_DEMAND_SERVER_MEDIA_SUBSESSION_HH
#include "OnDemandServerMediaSubsession.hh"
#endif

class FileServerMediaSubsession: public OnDemandServerMediaSubsession {
protected: // we're a virtual base class
  FileServerMediaSubsession(UsageEnvironment& env, char const* fileName,
			    Boolean reuseFirstSource);
  virtual ~FileServerMediaSubsession();

protected:
  char const* fFileName;
  u_int64_t fFileSize; // if known
};

#endif
