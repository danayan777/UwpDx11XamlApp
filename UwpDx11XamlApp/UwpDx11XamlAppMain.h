#pragma once

#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"
#include "Content\SampleFpsTextRenderer.h"

// Direct2D および 3D コンテンツを画面上でレンダリングします。
namespace UwpDx11XamlApp
{
	class UwpDx11XamlAppMain : public DX::IDeviceNotify
	{
	public:
		UwpDx11XamlAppMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~UwpDx11XamlAppMain();
		void CreateWindowSizeDependentResources();
		void StartTracking() { m_sceneRenderer->StartTracking(); }
		void TrackingUpdate(float positionX) { m_pointerLocationX = positionX; }
		void StopTracking() { m_sceneRenderer->StopTracking(); }
		bool IsTracking() { return m_sceneRenderer->IsTracking(); }
		void StartRenderLoop();
		void StopRenderLoop();
		Concurrency::critical_section& GetCriticalSection() { return m_criticalSection; }

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

	private:
		void ProcessInput();
		void Update();
		bool Render();

		// デバイス リソースへのキャッシュされたポインター。
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: これを独自のコンテンツ レンダラーで置き換えます。
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;

		Windows::Foundation::IAsyncAction^ m_renderLoopWorker;
		Concurrency::critical_section m_criticalSection;

		// ループ タイマーをレンダリングしています。
		DX::StepTimer m_timer;

		// 現在の入力ポインターの位置を追跡します。
		float m_pointerLocationX;
	};
}