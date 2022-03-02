#ifndef __dvbci_dvbci_h
#define __dvbci_dvbci_h

#ifndef SWIG

#include <lib/base/ebase.h>
#include <lib/base/message.h>
#include <lib/base/thread.h>
#include <lib/service/iservice.h>
#ifdef __sh__
#include <lib/base/thread.h>
#endif
#include <lib/python/python.h>
#include <set>
#include <queue>

class eDVBCISession;
class eDVBCIApplicationManagerSession;
class eDVBCICAManagerSession;
class eDVBCICcSession;
class eDVBCIMMISession;
class eDVBServicePMTHandler;
class eDVBCISlot;
class eDVBCIInterfaces;

struct queueData
{
	uint8_t prio;
	unsigned char *data;
	unsigned int len;
	queueData( unsigned char *data, unsigned int len, uint8_t prio = 0 )
		:prio(prio), data(data), len(len)
	{

	}
	bool operator < ( const struct queueData &a ) const
	{
		return prio < a.prio;
	}
};

typedef std::pair<std::string, uint32_t> providerPair;
typedef std::set<providerPair> providerSet;
typedef std::set<uint16_t> caidSet;
typedef std::set<eServiceReference> serviceSet;

#ifdef __sh__
/* ********************************** */
/* constants taken from dvb-apps 
 */
#define T_SB                0x80	// sb                           primitive   h<--m
#define T_RCV               0x81	// receive                      primitive   h-->m
#define T_CREATE_T_C        0x82	// create transport connection  primitive   h-->m
#define T_C_T_C_REPLY       0x83	// ctc reply                    primitive   h<--m
#define T_DELETE_T_C        0x84	// delete tc                    primitive   h<->m
#define T_D_T_C_REPLY       0x85	// dtc reply                    primitive   h<->m
#define T_REQUEST_T_C       0x86	// request transport connection primitive   h<--m
#define T_NEW_T_C           0x87	// new tc / reply to t_request  primitive   h-->m
#define T_T_C_ERROR         0x77	// error creating tc            primitive   h-->m
#define T_DATA_LAST         0xA0	// convey data from higher      constructed h<->m
				 // layers
#define T_DATA_MORE         0xA1	// convey data from higher      constructed h<->m
				 // layers

typedef enum {eDataTimeout, eDataError, eDataReady, eDataWrite, eDataStatusChanged} eData;

static inline int time_after(struct timespec oldtime, uint32_t delta_ms)
{
	// calculate the oldtime + add on the delta
	uint64_t oldtime_ms = (oldtime.tv_sec * 1000) + (oldtime.tv_nsec / 1000000);
	oldtime_ms += delta_ms;

	// calculate the nowtime
	struct timespec nowtime;
	clock_gettime(CLOCK_MONOTONIC, &nowtime);
	uint64_t nowtime_ms = (nowtime.tv_sec * 1000) + (nowtime.tv_nsec / 1000000);

	// check
	return nowtime_ms > oldtime_ms;
}
#endif

class eDVBCISlot: public iObject, public sigc::trackable
{
	friend class eDVBCIInterfaces;
	DECLARE_REF(eDVBCISlot);
	int slotid;
	int fd;
	ePtr<eSocketNotifier> notifier;
	int state;
	int m_ci_version;
	std::map<uint16_t, uint8_t> running_services;
	eDVBCIApplicationManagerSession *application_manager;
	eDVBCICAManagerSession *ca_manager;
	eDVBCICcSession *cc_manager;
	eDVBCIMMISession *mmi_session;
	std::priority_queue<queueData> sendqueue;
	caidSet possible_caids;
	serviceSet possible_services;
	providerSet possible_providers;
	int use_count;
	eDVBCISlot *linked_next; // needed for linked CI handling
	std::string current_source;
	int current_tuner;
	bool user_mapped;
	void data(int);
	bool plugged;
<<<<<<< HEAD
#ifdef __sh__
	//dagobert
	char connection_id;
	bool mmi_active;
	int receivedLen;
	unsigned char* receivedData;
#endif
public:
	enum {stateRemoved, stateInserted, stateInvalid, stateResetted};
	eDVBCISlot(eMainloop *context, int nr);
	~eDVBCISlot();

	int send(const unsigned char *data, size_t len);

	void setAppManager( eDVBCIApplicationManagerSession *session );
	void setMMIManager( eDVBCIMMISession *session );
	void setCAManager( eDVBCICAManagerSession *session );
=======
>>>>>>> 4cf2ad3c93680791dc065098aeaec5f28fef9daf

	eDVBCIApplicationManagerSession *getAppManager() { return application_manager; }
	eDVBCIMMISession *getMMIManager() { return mmi_session; }
	eDVBCICAManagerSession *getCAManager() { return ca_manager; }
	eDVBCICcSession *getCCManager() { return cc_manager; }

	int getState() { return state; }
	int reset();
	int startMMI();
	int stopMMI();
	int answerText(int answer);
	int answerEnq(char *value);
	int cancelEnq();
	int getMMIState();
	int sendCAPMT(eDVBServicePMTHandler *ptr, const std::vector<uint16_t> &caids=std::vector<uint16_t>());
	void removeService(uint16_t program_number=0xFFFF);
	int setSource(const std::string &source);
	int setClockRate(int);
	void determineCIVersion();
	static std::string getTunerLetter(int tuner_no) { return std::string(1, char(65 + tuner_no)); }
<<<<<<< HEAD
#ifdef __sh__
	bool checkQueueSize();
	void thread();
	void mmiOpened() { mmi_active = true; };
	void mmiClosed() { mmi_active = false; };
	void process_tpdu(unsigned char tpdu_tag, __u8* data, int asn_data_length, int con_id);
	bool sendCreateTC();
	eData sendData(unsigned char* data, int len);
	struct timeval tx_time;
	struct timespec last_poll_time;
#endif
=======
public:
	enum {stateRemoved, stateInserted, stateInvalid, stateResetted};
	enum {versionUnknown = -1, versionCI = 0, versionCIPlus1 = 1, versionCIPlus2 = 2};
	eDVBCISlot(eMainloop *context, int nr);
	~eDVBCISlot();

	int send(const unsigned char *data, size_t len);

	void setAppManager( eDVBCIApplicationManagerSession *session );
	void setMMIManager( eDVBCIMMISession *session );
	void setCAManager( eDVBCICAManagerSession *session );
	void setCCManager( eDVBCICcSession *session );

	int getSlotID();
	int getNumOfServices();
	int getVersion();
>>>>>>> 4cf2ad3c93680791dc065098aeaec5f28fef9daf
};

struct CIPmtHandler
{
	eDVBServicePMTHandler *pmthandler;
	eDVBCISlot *cislot;
	CIPmtHandler()
		:pmthandler(NULL), cislot(NULL)
	{}
	CIPmtHandler( const CIPmtHandler &x )
		:pmthandler(x.pmthandler), cislot(x.cislot)
	{}
	CIPmtHandler( eDVBServicePMTHandler *ptr )
		:pmthandler(ptr), cislot(NULL)
	{}
	bool operator==(const CIPmtHandler &x) const { return x.pmthandler == pmthandler; }
};

typedef std::list<CIPmtHandler> PMTHandlerList;

#endif // SWIG

class eDVBCIInterfaces: public eMainloop, private eThread
{
private:
	typedef enum
	{
		interface_none,
		interface_use_dvr,
		interface_use_pvr,
	} stream_interface_t;

	typedef enum
	{
		finish_none,
		finish_use_tuner_a,
		finish_use_pvr_none,
		finish_use_none,
	} stream_finish_mode_t;

	DECLARE_REF(eDVBCIInterfaces);

	stream_interface_t m_stream_interface;
	stream_finish_mode_t m_stream_finish_mode;

	static eDVBCIInterfaces *instance;
	eSmartPtrList<eDVBCISlot> m_slots;
	eDVBCISlot *getSlot(int slotid);
	PMTHandlerList m_pmt_handlers;
	std::string m_language;
	eFixedMessagePump<int> m_messagepump_thread; // message handling in the thread
	eFixedMessagePump<int> m_messagepump_main; // message handling in the e2 mainloop
	ePtr<eTimer> m_runTimer; // workaround to interrupt thread mainloop as some ci drivers don't implement poll properly
	static pthread_mutex_t m_pmt_handler_lock;
	bool m_ciplus_routing_active;
	int m_ciplus_routing_tunernum;
	std::string m_ciplus_routing_input;
	std::string m_ciplus_routing_ci_input;

	int sendCAPMT(int slot);

	void thread();
	void gotMessageThread(const int &message);
	void gotMessageMain(const int &message);

#ifndef SWIG
public:
#endif
	eDVBCIInterfaces();
	~eDVBCIInterfaces();

	static pthread_mutex_t m_slot_lock;

	void addPMTHandler(eDVBServicePMTHandler *pmthandler);
	void removePMTHandler(eDVBServicePMTHandler *pmthandler);
	void recheckPMTHandlers();
	void executeRecheckPMTHandlersInMainloop();
	void gotPMT(eDVBServicePMTHandler *pmthandler);
	void ciRemoved(eDVBCISlot *slot);
	int getSlotState(int slot);

	int reset(int slot);
	int initialize(int slot);
	int startMMI(int slot);
	int stopMMI(int slot);
	int answerText(int slot, int answer);
	int answerEnq(int slot, char *value);
	int cancelEnq(int slot);
	int getMMIState(int slot);
	int setInputSource(int tunerno, const std::string &source);
	int setCIClockRate(int slot, int rate);
	void setCIPlusRouting(int slotid);
	void revertCIPlusRouting(int slotid);
	bool canDescrambleMultipleServices(eDVBCISlot* slot);
	std::string getLanguage() { return m_language; };
#ifdef SWIG
public:
#endif
	static eDVBCIInterfaces *getInstance();
	int getNumOfSlots() { return m_slots.size(); }
	PyObject *getDescrambleRules(int slotid);
	RESULT setDescrambleRules(int slotid, SWIG_PYOBJECT(ePyObject) );
	PyObject *readCICaIds(int slotid);
	struct Message
	{
		enum
		{
			slotStateChanged,
			mmiSessionDestroyed,
			mmiDataReceived,
			appNameChanged
		};
		int m_type;
		int m_slotid;
		int m_state;
		unsigned char m_tag[3];
		unsigned char m_data[4096];
		int m_len;
		std::string m_appName;
		Message(int type, int slotid): m_type(type), m_slotid(slotid) {};
		Message(int type, int slotid, int state): m_type(type), m_slotid(slotid), m_state(state) {};
		Message(int type, int slotid, std::string appName): m_type(type), m_slotid(slotid), m_appName(appName) {};
		Message(int type, int slotid, const unsigned char* tag, unsigned char* data, int len): m_type(type), m_slotid(slotid), m_len(len)
		{
			memcpy(m_tag, tag, 3);
			memcpy(m_data, data, len);
		};
	};

};

#endif
