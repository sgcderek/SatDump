#include "core/plugin.h"
#include "logger.h"
#include "hackrf_sdr_source.h"
#include "hackrf_sdr_sink.h"

class HackRFSDRSupport : public satdump::Plugin
{
public:
    std::string getID()
    {
        return "hackrf_sdr_support";
    }

    void init()
    {
        satdump::eventBus->register_handler<dsp::RegisterDSPSampleSourcesEvent>(registerSources);
        satdump::eventBus->register_handler<dsp::RegisterDSPSampleSinksEvent>(registerSinks);
        hackrf_init();
    }

    static void registerSources(const dsp::RegisterDSPSampleSourcesEvent &evt)
    {
        evt.dsp_sources_registry.insert({HackRFSource::getID(), {HackRFSource::getInstance, HackRFSource::getAvailableSources}});
    }

    static void registerSinks(const dsp::RegisterDSPSampleSinksEvent &evt)
    {
        evt.dsp_sinks_registry.insert({HackRFSink::getID(), {HackRFSink::getInstance, HackRFSink::getAvailableSinks}});
    }
};

PLUGIN_LOADER(HackRFSDRSupport)