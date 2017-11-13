#include "EngineClock.h"

EngineClock::EngineClock(): FrameCount(0)
{
	lastEngineTime = engineClock.now();
	lastFrameTime = frameTimer.now();

	startPhysicsTime = physicsTimer.now();
	startRenderTime = renderTimer.now();
	startUpdateTime = updateTimer.now();

	endPhysicsTime = startPhysicsTime;
	endRenderTime = startRenderTime;
	endUpdateTime = startUpdateTime;

}

float EngineClock::EngineElapsedSeconds()
{
	const std::chrono::time_point<std::chrono::high_resolution_clock> now = engineClock.now();
	const float delta = std::chrono::duration_cast<std::chrono::seconds>(now - lastEngineTime).count();
	lastFrameTime = now;
	return delta;
}

float EngineClock::EngineElapsedMilliseconds()
{
	const std::chrono::time_point<std::chrono::high_resolution_clock> now = engineClock.now();
	const float delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastEngineTime).count();
	lastFrameTime = now;
	return delta;
}

float EngineClock::EngineElapsedMicroseconds()
{
	const std::chrono::time_point<std::chrono::high_resolution_clock> now = engineClock.now();
	const float delta = std::chrono::duration_cast<std::chrono::microseconds>(now - lastEngineTime).count();
	lastFrameTime = now;
	return delta;
}

float EngineClock::EngineElapsedNanoseconds()
{
	const std::chrono::time_point<std::chrono::high_resolution_clock> now = engineClock.now();
	const float delta = std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastEngineTime).count();
	lastFrameTime = now;
	return delta;
}

float EngineClock::PhysicsAverageSeconds() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(physicsTime).count() / FrameCount;
}

float EngineClock::UpdateAverageSeconds() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(updateTime).count() / FrameCount;
}

float EngineClock::RenderAverageSeconds() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(renderTime).count() / FrameCount;
}

float EngineClock::PhysicsAverage() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(physicsTime).count() / FrameCount;
}

float EngineClock::UpdateAverage() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(updateTime).count() / FrameCount;
}

float EngineClock::RenderAverage() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(renderTime).count() / FrameCount;
}

void EngineClock::StartPhysicsTimer()
{
	startPhysicsTime = physicsTimer.now();
}

void EngineClock::StopPhysicsTimer()
{
	endPhysicsTime = physicsTimer.now();
	physicsTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endPhysicsTime - startPhysicsTime);
}

void EngineClock::StartUpdateTimer()
{
	startUpdateTime = updateTimer.now();
}

void EngineClock::StopUpdateTimer()
{
	endUpdateTime = updateTimer.now();
	updateTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endUpdateTime - startUpdateTime);
}

void EngineClock::StartRenderTimer()
{
	startRenderTime = renderTimer.now();
}

void EngineClock::StopRenderTimer()
{
	endRenderTime = renderTimer.now();
	renderTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endRenderTime - startRenderTime);
}

///
/// Returns Frame Delta in Milliseconds
///
float EngineClock::GetFrameDelta()
{
	++FrameCount;
	const std::chrono::time_point<std::chrono::high_resolution_clock> now = frameTimer.now();
	const float delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrameTime).count();
	lastFrameTime = now;
	return delta;
}

///
/// Returns Frame Delta in Seconds
///
float EngineClock::GetFrameDeltaSeconds()
{
	return GetFrameDelta() / 1000.0f;
}

void EngineClock::Reset()
{
	FrameCount = 0;

	startPhysicsTime = physicsTimer.now();
	startRenderTime = renderTimer.now();
	startUpdateTime = updateTimer.now();

	endPhysicsTime = startPhysicsTime;
	endRenderTime = startRenderTime;
	endUpdateTime = startUpdateTime;

	physicsTime = std::chrono::duration<long long, std::ratio<1, 1000000000>>::zero();
	renderTime = std::chrono::duration<long long, std::ratio<1, 1000000000>>::zero();
	updateTime = std::chrono::duration<long long, std::ratio<1, 1000000000>>::zero();
}
