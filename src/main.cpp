#include "nle/Window.h"
#include "nle/Scene.h"
#include "nle/Renderer3D.h"
#include "nle/Texture.h"
#include "nle/Mesh.h"
#include "nle/Model.h"
#include "nle/Nle.h"

#include <glm/gtc/random.hpp>

#include "FastNoiseLite.h"

int main(int argc, char *argv[])
{
	nle::Nle app;

	app.currentScene()->camera()->setPosition({0.f, 200.f, -200.f});
	app.currentScene()->camera()->setRotation({0.f, 90.f, 0.f});
	app.currentScene()->light()->setAmbientIntensity(.05f);
	app.currentScene()->light()->setDiffuseIntensity(1.f);
	app.currentScene()->light()->setRotation(glm::vec3(2.f, -1.f, -2.f));
	app.currentScene()->light()->setEnabled(true);

	app.textureFactory()->load("models/hasan/hasan.jpg", "hasan");

	app.physicsEngine()->bindPhysicsTickCallback([&](double delta){
		if(app.currentScene())
		{
			float intensity = app.currentScene()->light()->ambientIntensity();
			constexpr const float step = 0.0166f * 0.2f;
			static int direction = 1;
			
			intensity += (step * direction);
			if(intensity > 1.0f)
			{
				intensity = 1.0f;
				direction *= -1;
			}
			else if(intensity < 0.0f)
			{
				intensity = 0.0f;
				direction *= -1;
			}

			app.currentScene()->light()->setAmbientIntensity(intensity);
		}
	});
	
	nle::Model modHasan(nle::DEFAULT_SHADER, app.textureFactory()->get("hasan"));
	if(modHasan.loadOBJ("models/hasan/hasan.obj"))
	{
		for(int i = 0; i < 10; i++)
		{
			auto rnd = glm::sphericalRand(200.f);
			nle::MultiMeshInstance *mm = modHasan.createInstance();
			// mm->setPosition(rnd + glm::vec3(0.f, 1000.f, 0.f));
			mm->setScale(glm::vec3(50.f));
			app.currentScene()->addChild(mm);
			// app.physicsEngine()->attachPhysicsBody(mm);
		}
	}

	app.run();

	return (0);
}
