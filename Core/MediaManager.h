#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <atomic>
#include <set>

#include "Core/Constant.h"
#include "Core/Singleton.h"
#include "Core/MediaHandleChain.h"
#include "IO/SqliteHelper.h"
#include "Core/MediaItem.h"
#include "Core/Event.h"

namespace XSPlayer {

    // nType = 1 init
    struct MediaInfo {
        int nType;
        size_t nDuration;
    };

    using InforCallback = std::function<void(const MediaInfo& infor)>;

    class MediaManager : public Singleton<MediaManager> {
        NON_COPY_ABLE(MediaManager)

    public:
        MediaManager(void);
        ~MediaManager(void) override;
        void Destory(void);

        void SetPlayMedia(size_t meidaID);
        bool PlayMedia(size_t meidaID);
        bool PlayMedia(void);
        bool Pause(void);
        bool Continue(void);
        void Stop(void);
        void Seek(long long pos);

        void AddHandleChain(const MediaHandleChainPtr& pHandleChain);

        bool AddMedia(const Media* pMedia, const String& type);
        bool DeleteMedia(unsigned int mediaID);
        const String& GetMediaPath(size_t mediaID) const;
        String GetMediaName(const size_t mediaID);
        Media* GetMedia(const size_t mediaID);
        int GetMediaCount(void) const;
        size_t GetCurrentPlay(void) const { return m_currentPlayMedia; }

        void SortLocalMediaByNumberName(void);

        static size_t GenerateMeidaId(void);

        bool RegistEvent(EventHandle* pEvent);
        bool UnregistEvent(EventHandle* pEvent);
        bool NotifyEvent(const EventPtr& event);

    public:
        bool AddMediaSource(MediaSourceFactory* pMediaSourceFactory);
        bool AddMediaContainter(const String& type);
        const MediaContainer* GetMediaContainer(const String& source) const;

    private:
        void Init(void);

    private:
        MediaHandleChainPtr m_pMediaHandleChane;
        InforCallback m_callback = nullptr;
        size_t m_currentPlayMedia = -1;
        MediaContainer* m_pRoot = nullptr;
        using ListMediaSourcePtr = std::unordered_map<MediaSourceType, MediaSourcePtr>;
        ListMediaSourcePtr m_listMediaSoruces;
        using ListEvent = std::set<EventHandle*>;
        ListEvent m_listEvent;
        static std::atomic<size_t> m_meidaCount;
    };
    using MediaManagerPtr = std::shared_ptr<MediaManager>;
}

#endif // MEDIAMANAGER_H
