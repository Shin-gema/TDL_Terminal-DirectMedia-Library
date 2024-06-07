
#ifndef TDL_TERMINAL_DIRECTMEDIA_LIBRARY_SOUNDBUFFER_HPP
    #define TDL_TERMINAL_DIRECTMEDIA_LIBRARY_SOUNDBUFFER_HPP

    #include <AL/al.h>
    #include <AL/alc.h>
    #include <string>
    #include <vector>
    #include <thread>
    #include <condition_variable>
    #include <mutex>
    #include <atomic>

    namespace tdl {
        class Sound {
            public:
                Sound(const std::string &device = "default");
                ~Sound();

                bool get_available_devices(std::vector<std::string>& devicesVec, ALCdevice* device);

                void loadFile(const std::string& filename);

                void play();
                void pause();
                void resume();
            private:
                void playImpl();
                ALCdevice* _device;
                ALCcontext* _context;
                std::vector<ALuint> _buffers;
                std::thread _playThread;
                std::atomic<bool> _isPaused{false};
                std::atomic<bool> _isChanged{false};
                bool _isPlaying;
        };
    }

#endif //TDL_TERMINAL_DIRECTMEDIA_LIBRARY_SOUNDBUFFER_HPP
