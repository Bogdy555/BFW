#include "../Headers/BFW.hpp"



template <typename T> static const bool EntityAddComponent(BFW::Vector<T>& _Components, BFW::SafePointer<T>& _Component, const T& _NewComponent)
{
	if ((T*)(_Component))
	{
		*_Component = _NewComponent;
		return true;
	}

	_Component = &_Components.PushBack(_NewComponent);

	return true;
}

template <typename T> static const bool EntityRemoveComponent(BFW::Vector<T>& _Components, BFW::SafePointer<T>& _Component)
{
	for (size_t _Index = 0; _Index < _Components.GetSize(); _Index++)
	{
		if (&_Components[_Index] == (T*)(_Component))
		{
			_Components.Erase(_Index);
			return true;
		}
	}

	_Component = nullptr;

	return false;
}



BFW::ECS::TransformComponent::TransformComponent() : Position(), Rotation(), ScaleByX(Math::Vec3(1.0f, 0.0f, 0.0f)), ScaleByY(Math::Vec3(0.0f, 1.0f, 0.0f)), ScaleByZ(Math::Vec3(0.0f, 0.0f, 1.0f)), FlipAxis()
{

}

BFW::ECS::TransformComponent::TransformComponent(const TransformComponent& _Other) : Position(_Other.Position), Rotation(_Other.Rotation), ScaleByX(_Other.ScaleByX), ScaleByY(_Other.ScaleByY), ScaleByZ(_Other.ScaleByZ), FlipAxis(_Other.FlipAxis)
{

}

BFW::ECS::TransformComponent::TransformComponent(TransformComponent&& _Other) noexcept : Position((Math::Vec3&&)(_Other.Position)), Rotation((Math::Vec3&&)(_Other.Rotation)), ScaleByX((Math::Vec3&&)(_Other.ScaleByX)), ScaleByY((Math::Vec3&&)(_Other.ScaleByY)), ScaleByZ((Math::Vec3&&)(_Other.ScaleByZ)), FlipAxis((Math::Vec3&&)(_Other.FlipAxis))
{

}

BFW::ECS::TransformComponent::~TransformComponent()
{

}

const bool BFW::ECS::TransformComponent::Deserialize(const Assets::Json& _Json)
{
	*this = TransformComponent();

	if (_Json.GetType() != Assets::_ObjectJsonType)
	{
		return false;
	}

	const Assets::JsonObjectData& _ObjectData = _Json.GetObjectData();

	if (_ObjectData.Tags.GetSize() != _ObjectData.Object.GetSize())
	{
		return false;
	}

	for (size_t _Index = 0; _Index < _ObjectData.Tags.GetSize(); _Index++)
	{
		if (_ObjectData.Tags[_Index] == "Position.x")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			Position.x = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Position.y")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			Position.y = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Position.z")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			Position.z = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Rotation.x")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			Rotation.x = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Rotation.y")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			Rotation.y = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Rotation.z")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			Rotation.z = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "ScaleByX.x")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			ScaleByX.x = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "ScaleByX.y")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			ScaleByX.y = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "ScaleByX.z")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			ScaleByX.z = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "ScaleByY.x")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			ScaleByY.x = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "ScaleByY.y")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			ScaleByY.y = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "ScaleByY.z")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			ScaleByY.z = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "ScaleByZ.x")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			ScaleByZ.x = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "ScaleByZ.y")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			ScaleByZ.y = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "ScaleByZ.z")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			ScaleByZ.z = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "FlipAxis.x")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			FlipAxis.x = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "FlipAxis.y")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			FlipAxis.y = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "FlipAxis.z")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = TransformComponent();
				return false;
			}

			FlipAxis.z = _ObjectData.Object[_Index].GetNumber();
			continue;
		}
	}

	return true;
}

const BFW::Assets::Json BFW::ECS::TransformComponent::Serialize() const
{
	Assets::Json _Result;

	_Result.SetObject();

	Assets::JsonObjectData& _ObjectData = _Result.GetObjectData();

	_ObjectData.Tags.PushBack("Position.x");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Position.x);

	_ObjectData.Tags.PushBack("Position.y");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Position.y);

	_ObjectData.Tags.PushBack("Position.z");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Position.z);

	_ObjectData.Tags.PushBack("Rotation.x");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Rotation.x);

	_ObjectData.Tags.PushBack("Rotation.y");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Rotation.y);

	_ObjectData.Tags.PushBack("Rotation.z");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Rotation.z);

	_ObjectData.Tags.PushBack("ScaleByX.x");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(ScaleByX.x);

	_ObjectData.Tags.PushBack("ScaleByX.y");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(ScaleByX.y);

	_ObjectData.Tags.PushBack("ScaleByX.z");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(ScaleByX.z);

	_ObjectData.Tags.PushBack("ScaleByY.x");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(ScaleByY.x);

	_ObjectData.Tags.PushBack("ScaleByY.y");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(ScaleByY.y);

	_ObjectData.Tags.PushBack("ScaleByY.z");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(ScaleByY.z);

	_ObjectData.Tags.PushBack("ScaleByZ.x");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(ScaleByZ.x);

	_ObjectData.Tags.PushBack("ScaleByZ.y");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(ScaleByZ.y);

	_ObjectData.Tags.PushBack("ScaleByZ.z");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(ScaleByZ.z);

	_ObjectData.Tags.PushBack("FlipAxis.x");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(FlipAxis.x);

	_ObjectData.Tags.PushBack("FlipAxis.y");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(FlipAxis.y);

	_ObjectData.Tags.PushBack("FlipAxis.z");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(FlipAxis.z);

	return _Result;
}

const BFW::Math::Mat4 BFW::ECS::TransformComponent::Model(const Entity* _Parent) const
{
	if (_Parent)
	{
		return
			_Parent->Transform.Model(_Parent->GetParent()) *
			Math::Mat4::GetTranslation(Position) *
			Math::Mat4::GetRotation(Rotation.y, Math::Vec3(0.0f, 1.0f, 0.0f)) *
			Math::Mat4::GetRotation(Rotation.x, Math::Vec3(1.0f, 0.0f, 0.0f)) *
			Math::Mat4::GetRotation(Rotation.z, Math::Vec3(0.0f, 0.0f, 1.0f)) *
			Math::Mat4(ScaleByX, ScaleByY, ScaleByZ) *
			Math::Mat4::GetFlip(FlipAxis);
	}

	return
		Math::Mat4::GetTranslation(Position) *
		Math::Mat4::GetRotation(Rotation.y, Math::Vec3(0.0f, 1.0f, 0.0f)) *
		Math::Mat4::GetRotation(Rotation.x, Math::Vec3(1.0f, 0.0f, 0.0f)) *
		Math::Mat4::GetRotation(Rotation.z, Math::Vec3(0.0f, 0.0f, 1.0f)) *
		Math::Mat4(ScaleByX, ScaleByY, ScaleByZ) *
		Math::Mat4::GetFlip(FlipAxis);
}

BFW::ECS::TransformComponent& BFW::ECS::TransformComponent::operator= (const TransformComponent& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Position = _Other.Position;
	Rotation = _Other.Rotation;
	ScaleByX = _Other.ScaleByX;
	ScaleByY = _Other.ScaleByY;
	ScaleByZ = _Other.ScaleByZ;
	FlipAxis = _Other.FlipAxis;

	return *this;
}

BFW::ECS::TransformComponent& BFW::ECS::TransformComponent::operator= (TransformComponent&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Position = (Math::Vec3&&)(_Other.Position);
	Rotation = (Math::Vec3&&)(_Other.Rotation);
	ScaleByX = (Math::Vec3&&)(_Other.ScaleByX);
	ScaleByY = (Math::Vec3&&)(_Other.ScaleByY);
	ScaleByZ = (Math::Vec3&&)(_Other.ScaleByZ);
	FlipAxis = (Math::Vec3&&)(_Other.FlipAxis);

	return *this;
}



BFW::ECS::CameraComponent::CameraComponent() : Position(), Rotation(), FieldOfView(90.0f), NearPlane(0.001f), FarPlane(1000.0f), Perspective(true), XRatioFOV(false), SafePointers()
{

}

BFW::ECS::CameraComponent::CameraComponent(const CameraComponent& _Other) : Position(_Other.Position), Rotation(_Other.Rotation), FieldOfView(_Other.FieldOfView), NearPlane(_Other.NearPlane), FarPlane(_Other.FarPlane), Perspective(_Other.Perspective), XRatioFOV(_Other.XRatioFOV), SafePointers()
{

}

BFW::ECS::CameraComponent::CameraComponent(CameraComponent&& _Other) noexcept : Position((Math::Vec3&&)(_Other.Position)), Rotation((Math::Vec3&&)(_Other.Rotation)), FieldOfView(_Other.FieldOfView), NearPlane(_Other.NearPlane), FarPlane(_Other.FarPlane), Perspective(_Other.Perspective), XRatioFOV(_Other.XRatioFOV), SafePointers()
{
	SafePointer<CameraComponent>::MoveAll(this, &_Other);

	_Other.FieldOfView = 90.0f;
	_Other.NearPlane = 0.001f;
	_Other.FarPlane = 1000.0f;
	_Other.Perspective = true;
	_Other.XRatioFOV = false;
}

BFW::ECS::CameraComponent::~CameraComponent()
{
	SafePointer<CameraComponent>::ReleaseAll(this);
}

const bool BFW::ECS::CameraComponent::Deserialize(const Assets::Json& _Json)
{
	*this = CameraComponent();

	if (_Json.GetType() != Assets::_ObjectJsonType)
	{
		return false;
	}

	const Assets::JsonObjectData& _ObjectData = _Json.GetObjectData();

	if (_ObjectData.Tags.GetSize() != _ObjectData.Object.GetSize())
	{
		return false;
	}

	for (size_t _Index = 0; _Index < _ObjectData.Tags.GetSize(); _Index++)
	{
		if (_ObjectData.Tags[_Index] == "Position.x")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = CameraComponent();
				return false;
			}

			Position.x = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Position.y")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = CameraComponent();
				return false;
			}

			Position.y = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Position.z")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = CameraComponent();
				return false;
			}

			Position.z = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Rotation.x")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = CameraComponent();
				return false;
			}

			Rotation.x = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Rotation.y")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = CameraComponent();
				return false;
			}

			Rotation.y = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Rotation.z")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = CameraComponent();
				return false;
			}

			Rotation.z = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "FieldOfView")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = CameraComponent();
				return false;
			}

			FieldOfView = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "NearPlane")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = CameraComponent();
				return false;
			}

			NearPlane = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "FarPlane")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = CameraComponent();
				return false;
			}

			FarPlane = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Perspective")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_BoolJsonType)
			{
				*this = CameraComponent();
				return false;
			}

			Perspective = _ObjectData.Object[_Index].GetBool();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "XRatioFOV")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_BoolJsonType)
			{
				*this = CameraComponent();
				return false;
			}

			XRatioFOV = _ObjectData.Object[_Index].GetBool();
			continue;
		}
	}

	return true;
}

const BFW::Assets::Json BFW::ECS::CameraComponent::Serialize() const
{
	Assets::Json _Result;

	_Result.SetObject();

	Assets::JsonObjectData& _ObjectData = _Result.GetObjectData();

	_ObjectData.Tags.PushBack("Position.x");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Position.x);

	_ObjectData.Tags.PushBack("Position.y");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Position.y);

	_ObjectData.Tags.PushBack("Position.z");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Position.z);

	_ObjectData.Tags.PushBack("Rotation.x");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Rotation.x);

	_ObjectData.Tags.PushBack("Rotation.y");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Rotation.y);

	_ObjectData.Tags.PushBack("Rotation.z");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Rotation.z);

	_ObjectData.Tags.PushBack("FieldOfView");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(FieldOfView);

	_ObjectData.Tags.PushBack("NearPlane");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(NearPlane);

	_ObjectData.Tags.PushBack("FarPlane");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(FarPlane);

	_ObjectData.Tags.PushBack("Perspective");
	_ObjectData.Object.PushBack(Assets::Json()).SetBool(Perspective);

	_ObjectData.Tags.PushBack("XRatioFOV");
	_ObjectData.Object.PushBack(Assets::Json()).SetBool(XRatioFOV);

	return _Result;
}

const BFW::Math::Mat4 BFW::ECS::CameraComponent::View() const
{
	return
		Math::Mat4::GetRotation(-Rotation.z, Math::Vec3(0.0f, 0.0f, 1.0f)) *
		Math::Mat4::GetRotation(-Rotation.x, Math::Vec3(1.0f, 0.0f, 0.0f)) *
		Math::Mat4::GetRotation(-Rotation.y, Math::Vec3(0.0f, 1.0f, 0.0f)) *
		Math::Mat4::GetTranslation(-Position);
}

const BFW::Math::Mat4 BFW::ECS::CameraComponent::Projection(const float _AspectRatio) const
{
	if (Perspective)
	{
		if (XRatioFOV)
		{
			return Math::Mat4::GetPerspectiveOxRightHand(FieldOfView, _AspectRatio, NearPlane, FarPlane);
		}

		return Math::Mat4::GetPerspectiveOyRightHand(FieldOfView, _AspectRatio, NearPlane, FarPlane);
	}

	if (XRatioFOV)
	{
		return Math::Mat4::GetOrthoRightHand(-FieldOfView / 2.0f, FieldOfView / 2.0f, -FieldOfView / 2.0f / _AspectRatio, FieldOfView / 2.0f / _AspectRatio, NearPlane, FarPlane);
	}

	return Math::Mat4::GetOrthoRightHand(-FieldOfView / 2.0f * _AspectRatio, FieldOfView / 2.0f * _AspectRatio, -FieldOfView / 2.0f, FieldOfView / 2.0f, NearPlane, FarPlane);
}

BFW::ECS::CameraComponent& BFW::ECS::CameraComponent::operator= (const CameraComponent& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Position = _Other.Position;
	Rotation = _Other.Rotation;
	FieldOfView = _Other.FieldOfView;
	NearPlane = _Other.NearPlane;
	FarPlane = _Other.FarPlane;
	Perspective = _Other.Perspective;
	XRatioFOV = _Other.XRatioFOV;

	return *this;
}

BFW::ECS::CameraComponent& BFW::ECS::CameraComponent::operator= (CameraComponent&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	SafePointer<CameraComponent>::MoveAll(this, &_Other);

	Position = (Math::Vec3&&)(_Other.Position);
	Rotation = (Math::Vec3&&)(_Other.Rotation);
	FieldOfView = _Other.FieldOfView;
	NearPlane = _Other.NearPlane;
	FarPlane = _Other.FarPlane;
	Perspective = _Other.Perspective;
	XRatioFOV = _Other.XRatioFOV;

	_Other.FieldOfView = 90.0f;
	_Other.NearPlane = 0.001f;
	_Other.FarPlane = 1000.0f;
	_Other.Perspective = true;
	_Other.XRatioFOV = false;

	return *this;
}



BFW::ECS::LightComponent::LightComponent() : Color(Math::Vec3(1.0f, 1.0f, 1.0f)), Intensity(1.0f), Direction(), ThetaCone(0.0f), ThetaFade(0.0f), SafePointers(), Type(_PointLightType)
{

}

BFW::ECS::LightComponent::LightComponent(const LightComponent& _Other) : Color(_Other.Color), Intensity(_Other.Intensity), Direction(_Other.Direction), ThetaCone(_Other.ThetaCone), ThetaFade(_Other.ThetaFade), SafePointers(), Type(_Other.Type)
{

}

BFW::ECS::LightComponent::LightComponent(LightComponent&& _Other) noexcept : Color(_Other.Color), Intensity(_Other.Intensity), Direction((Math::Vec3&&)(_Other.Direction)), ThetaCone(_Other.ThetaCone), ThetaFade(_Other.ThetaFade), SafePointers(), Type(_Other.Type)
{
	SafePointer<LightComponent>::MoveAll(this, &_Other);

	_Other.Color = Math::Vec3(1.0f, 1.0f, 1.0f);
	_Other.Intensity = 1.0f;
	_Other.ThetaCone = 0.0f;
	_Other.ThetaFade = 0.0f;
	_Other.Type = _PointLightType;
}

BFW::ECS::LightComponent::~LightComponent()
{
	SafePointer<LightComponent>::ReleaseAll(this);
}

const bool BFW::ECS::LightComponent::Deserialize(const Assets::Json& _Json)
{
	*this = LightComponent();

	if (_Json.GetType() != Assets::_ObjectJsonType)
	{
		return false;
	}

	const Assets::JsonObjectData& _ObjectData = _Json.GetObjectData();

	if (_ObjectData.Tags.GetSize() != _ObjectData.Object.GetSize())
	{
		return false;
	}

	for (size_t _Index = 0; _Index < _ObjectData.Tags.GetSize(); _Index++)
	{
		if (_ObjectData.Tags[_Index] == "Type")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = LightComponent();
				return false;
			}

			float _Type = (uint8_t)(_ObjectData.Object[_Index].GetNumber());

			if (_Type < 0.0f || _Type > 2.0f || _Type != floorf(_Type))
			{
				*this = LightComponent();
				return false;
			}

			Type = (uint8_t)(_Type);

			continue;
		}

		if (_ObjectData.Tags[_Index] == "Color.x")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = LightComponent();
				return false;
			}

			Color.x = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Color.y")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = LightComponent();
				return false;
			}

			Color.y = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Color.z")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = LightComponent();
				return false;
			}

			Color.z = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Intensity")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = LightComponent();
				return false;
			}

			Intensity = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Direction.x")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = LightComponent();
				return false;
			}

			Direction.x = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Direction.y")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = LightComponent();
				return false;
			}

			Direction.y = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "Direction.z")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = LightComponent();
				return false;
			}

			Direction.z = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "ThetaCone")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = LightComponent();
				return false;
			}

			ThetaCone = _ObjectData.Object[_Index].GetNumber();
			continue;
		}

		if (_ObjectData.Tags[_Index] == "ThetaFade")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_NumberJsonType)
			{
				*this = LightComponent();
				return false;
			}

			ThetaFade = _ObjectData.Object[_Index].GetNumber();
			continue;
		}
	}

	return true;
}

void BFW::ECS::LightComponent::SetType(const uint8_t _Type)
{
	if (_Type > 2)
	{
		throw nullptr;
	}

	Type = _Type;
}

const BFW::Assets::Json BFW::ECS::LightComponent::Serialize() const
{
	Assets::Json _Result;

	_Result.SetObject();

	Assets::JsonObjectData& _ObjectData = _Result.GetObjectData();

	_ObjectData.Tags.PushBack("Type");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Type);

	_ObjectData.Tags.PushBack("Color.x");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Color.x);

	_ObjectData.Tags.PushBack("Color.y");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Color.y);

	_ObjectData.Tags.PushBack("Color.z");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Color.z);

	_ObjectData.Tags.PushBack("Intensity");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Intensity);

	_ObjectData.Tags.PushBack("Direction.x");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Direction.x);

	_ObjectData.Tags.PushBack("Direction.y");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Direction.y);

	_ObjectData.Tags.PushBack("Direction.z");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(Direction.z);

	_ObjectData.Tags.PushBack("ThetaCone");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(ThetaCone);

	_ObjectData.Tags.PushBack("ThetaFade");
	_ObjectData.Object.PushBack(Assets::Json()).SetNumber(ThetaFade);

	return _Result;
}

const uint8_t BFW::ECS::LightComponent::GetType() const
{
	return Type;
}

BFW::ECS::LightComponent& BFW::ECS::LightComponent::operator= (const LightComponent& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Color = _Other.Color;
	Intensity = _Other.Intensity;
	Direction = _Other.Direction;
	ThetaCone = _Other.ThetaCone;
	ThetaFade = _Other.ThetaFade;
	Type = _Other.Type;

	return *this;
}

BFW::ECS::LightComponent& BFW::ECS::LightComponent::operator= (LightComponent&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	SafePointer<LightComponent>::MoveAll(this, &_Other);

	Color = _Other.Color;
	Intensity = _Other.Intensity;
	Direction = (Math::Vec3&&)(_Other.Direction);
	ThetaCone = _Other.ThetaCone;
	ThetaFade = _Other.ThetaFade;
	Type = _Other.Type;

	_Other.Color = Math::Vec3(1.0f, 1.0f, 1.0f);
	_Other.Intensity = 1.0f;
	_Other.ThetaCone = 0.0f;
	_Other.ThetaFade = 0.0f;
	_Other.Type = _PointLightType;

	return *this;
}



BFW::ECS::ScriptComponent::ScriptComponent() : SafePointers(), ScriptLibName(BFW_STRING_PREFIX("")), ScriptLib(), NameSpace(BFW_STRING_PREFIX("")), Object(), SerializedData()
{

}

BFW::ECS::ScriptComponent::ScriptComponent(const ScriptComponent& _Other) : SafePointers(), ScriptLibName(_Other.ScriptLibName), ScriptLib(_Other.ScriptLib), NameSpace(_Other.NameSpace), Object(_Other.Object), SerializedData(_Other.SerializedData)
{

}

BFW::ECS::ScriptComponent::ScriptComponent(ScriptComponent&& _Other) noexcept : SafePointers(), ScriptLibName(_Other.ScriptLibName), ScriptLib((SharedPointer<Assets::ScriptLib>&&)(_Other.ScriptLib)), NameSpace(_Other.NameSpace), Object((Assets::Json&&)(_Other.Object)), SerializedData((Assets::Json&&)(_Other.SerializedData))
{
	SafePointer<ScriptComponent>::MoveAll(this, &_Other);

	_Other.ScriptLibName = BFW_STRING_PREFIX("");
	_Other.NameSpace = BFW_STRING_PREFIX("");
}

BFW::ECS::ScriptComponent::~ScriptComponent()
{
	SafePointer<ScriptComponent>::ReleaseAll(this);
}

const bool BFW::ECS::ScriptComponent::Deserialize(const Assets::Json& _Json)
{
	*this = ScriptComponent();

	if (_Json.GetType() != Assets::_ObjectJsonType)
	{
		return false;
	}

	const Assets::JsonObjectData& _ObjectData = _Json.GetObjectData();

	if (_ObjectData.Tags.GetSize() != 3 ||
		_ObjectData.Tags[0] != "ScriptLibName" ||
		_ObjectData.Tags[1] != "NameSpace" ||
		_ObjectData.Tags[2] != "SerializedData" ||
		_ObjectData.Object.GetSize() != 3 ||
		_ObjectData.Object[0].GetType() != Assets::_StringJsonType ||
		_ObjectData.Object[1].GetType() != Assets::_StringJsonType)
	{
		return false;
	}

	bool _Error = false;

	ScriptLibName = BFW_UTF8_TO_MACHINE(_ObjectData.Object[0].GetString(), &_Error);

	if (_Error)
	{
		*this = ScriptComponent();
		return false;
	}

	NameSpace = BFW_UTF8_TO_MACHINE(_ObjectData.Object[1].GetString(), &_Error);

	if (_Error)
	{
		*this = ScriptComponent();
		return false;
	}

	SerializedData = _ObjectData.Object[2];

	return true;
}

void BFW::ECS::ScriptComponent::SetScript(const BFW_STRING_VIEW_TYPE& _ScriptLibName, const SharedPointer<Assets::ScriptLib> _ScriptLib, const BFW_STRING_VIEW_TYPE& _NameSpace)
{
	ScriptLibName = _ScriptLibName;
	ScriptLib = _ScriptLib;
	NameSpace = _NameSpace;
	Object = Assets::Json();
	SerializedData = Assets::Json();
}

void BFW::ECS::ScriptComponent::OnSetup(Entity& _Entity, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene)
{
	if (!(Assets::ScriptLib*)(ScriptLib))
	{
		return;
	}

	void (*_Symbol)(Entity& _Entity, Assets::Json& _Object, Assets::Json& _SerializedData, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene) =
		(void (*)(Entity& _Entity, Assets::Json& _Object, Assets::Json& _SerializedData, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene))
		(ScriptLib->GetSymbol(NameSpace, BFW_STRING_PREFIX("OnSetup")));

	if (!_Symbol)
	{
		return;
	}

	_Symbol(_Entity, Object, SerializedData, _Application, _Menu, _Manager, _Scene);
}

void BFW::ECS::ScriptComponent::OnUpdate(Entity& _Entity, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene)
{
	if (!(Assets::ScriptLib*)(ScriptLib))
	{
		return;
	}

	void (*_Symbol)(Entity& _Entity, Assets::Json& _Object, Assets::Json& _SerializedData, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene) =
		(void (*)(Entity& _Entity, Assets::Json& _Object, Assets::Json& _SerializedData, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene))
		(ScriptLib->GetSymbol(NameSpace, BFW_STRING_PREFIX("OnUpdate")));

	if (!_Symbol)
	{
		return;
	}

	_Symbol(_Entity, Object, SerializedData, _Application, _Menu, _Manager, _Scene);
}

void BFW::ECS::ScriptComponent::OnLateUpdate(Entity& _Entity, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene)
{
	if (!(Assets::ScriptLib*)(ScriptLib))
	{
		return;
	}

	void (*_Symbol)(Entity& _Entity, Assets::Json& _Object, Assets::Json& _SerializedData, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene) =
		(void (*)(Entity& _Entity, Assets::Json& _Object, Assets::Json& _SerializedData, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene))
		(ScriptLib->GetSymbol(NameSpace, BFW_STRING_PREFIX("OnLateUpdate")));

	if (!_Symbol)
	{
		return;
	}

	_Symbol(_Entity, Object, SerializedData, _Application, _Menu, _Manager, _Scene);
}

void BFW::ECS::ScriptComponent::OnFixedUpdate(Entity& _Entity, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene)
{
	if (!(Assets::ScriptLib*)(ScriptLib))
	{
		return;
	}

	void (*_Symbol)(Entity& _Entity, Assets::Json& _Object, Assets::Json& _SerializedData, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene) =
		(void (*)(Entity& _Entity, Assets::Json& _Object, Assets::Json& _SerializedData, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene))
		(ScriptLib->GetSymbol(NameSpace, BFW_STRING_PREFIX("OnFixedUpdate")));

	if (!_Symbol)
	{
		return;
	}

	_Symbol(_Entity, Object, SerializedData, _Application, _Menu, _Manager, _Scene);
}

void BFW::ECS::ScriptComponent::OnRender(Entity& _Entity, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene)
{
	if (!(Assets::ScriptLib*)(ScriptLib))
	{
		return;
	}

	void (*_Symbol)(Entity& _Entity, Assets::Json& _Object, Assets::Json& _SerializedData, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene) =
		(void (*)(Entity& _Entity, Assets::Json& _Object, Assets::Json& _SerializedData, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene))
		(ScriptLib->GetSymbol(NameSpace, BFW_STRING_PREFIX("OnRender")));

	if (!_Symbol)
	{
		return;
	}

	_Symbol(_Entity, Object, SerializedData, _Application, _Menu, _Manager, _Scene);
}

void BFW::ECS::ScriptComponent::OnStop(Entity& _Entity, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene)
{
	if (!(Assets::ScriptLib*)(ScriptLib))
	{
		Object = Assets::Json();
		return;
	}

	void (*_Symbol)(Entity& _Entity, Assets::Json& _Object, Assets::Json& _SerializedData, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene) =
		(void (*)(Entity& _Entity, Assets::Json& _Object, Assets::Json& _SerializedData, RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager, Scene& _Scene))
		(ScriptLib->GetSymbol(NameSpace, BFW_STRING_PREFIX("OnStop")));

	if (!_Symbol)
	{
		Object = Assets::Json();
		return;
	}

	_Symbol(_Entity, Object, SerializedData, _Application, _Menu, _Manager, _Scene);
	Object = Assets::Json();
}

const BFW::Assets::Json BFW::ECS::ScriptComponent::Serialize() const
{
	if (!ScriptLibName.size())
	{
		return Assets::Json();
	}

	Assets::Json _Result;

	_Result.SetObject();

	Assets::JsonObjectData& _ObjectData = _Result.GetObjectData();

	bool _Error = false;

	_ObjectData.Tags.PushBack("ScriptLibName");
	_ObjectData.Object.PushBack(Assets::Json()).SetString(BFW_MACHINE_TO_UTF8(ScriptLibName, &_Error).c_str());

	if (_Error)
	{
		return Assets::Json();
	}

	_ObjectData.Tags.PushBack("NameSpace");
	_ObjectData.Object.PushBack(Assets::Json()).SetString(BFW_MACHINE_TO_UTF8(NameSpace, &_Error).c_str());

	if (_Error)
	{
		return Assets::Json();
	}

	_ObjectData.Tags.PushBack("SerializedData");
	_ObjectData.Object.PushBack(SerializedData);

	return _Result;
}

const BFW_STRING_TYPE& BFW::ECS::ScriptComponent::GetScriptLibName() const
{
	return ScriptLibName;
}

const BFW_STRING_TYPE& BFW::ECS::ScriptComponent::GetNameSpace() const
{
	return NameSpace;
}

const BFW::Assets::Json& BFW::ECS::ScriptComponent::GetSerializedData() const
{
	return SerializedData;
}

BFW::ECS::ScriptComponent& BFW::ECS::ScriptComponent::operator= (const ScriptComponent& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	ScriptLibName = _Other.ScriptLibName;
	ScriptLib = _Other.ScriptLib;
	NameSpace = _Other.NameSpace;
	Object = _Other.Object;
	SerializedData = _Other.SerializedData;

	return *this;
}

BFW::ECS::ScriptComponent& BFW::ECS::ScriptComponent::operator= (ScriptComponent&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	SafePointer<ScriptComponent>::MoveAll(this, &_Other);

	ScriptLibName = _Other.ScriptLibName;
	ScriptLib = (SharedPointer<Assets::ScriptLib>&&)(_Other.ScriptLib);
	NameSpace = _Other.NameSpace;
	Object = (Assets::Json&&)(_Other.Object);
	SerializedData = (Assets::Json&&)(_Other.SerializedData);

	_Other.ScriptLibName = BFW_STRING_PREFIX("");
	_Other.NameSpace = BFW_STRING_PREFIX("");

	return *this;
}



BFW::ECS::Entity::Entity() : Transform(), SafePointers(), CurrentScene(nullptr), GUID(GUID::GetString()), Name(BFW_STRING_PREFIX("Name")), TagsList(), Tags(), Parent(nullptr), Children(), Camera(), Light(), Script()
{

}

BFW::ECS::Entity::Entity(const Entity& _Other) : Transform(_Other.Transform), SafePointers(), CurrentScene(_Other.CurrentScene), GUID(GUID::GetString()), Name(_Other.Name), TagsList(_Other.TagsList), Tags(_Other.Tags), Parent(nullptr), Children(_Other.Children), Camera(), Light(), Script()
{
	for (size_t _Index = 0; _Index < Children.GetSize(); _Index++)
	{
		Children[_Index].Parent = this;
	}

	if (!CurrentScene)
	{
		return;
	}

	if ((const CameraComponent*)(_Other.Camera))
	{
		AddCameraComponent(*_Other.Camera);
	}

	if ((const LightComponent*)(_Other.Light))
	{
		AddLightComponent(*_Other.Light);
	}

	if ((const ScriptComponent*)(_Other.Script))
	{
		AddScriptComponent(*_Other.Script);
	}
}

BFW::ECS::Entity::Entity(Entity&& _Other) noexcept : Transform((TransformComponent&&)(_Other.Transform)), SafePointers(), CurrentScene(_Other.CurrentScene), GUID(_Other.GUID), Name(_Other.Name), TagsList((Vector<BFW_STRING_TYPE>&&)(_Other.TagsList)), Tags((Trie<bool>&&)(_Other.Tags)), Parent((SafePointer<Entity>&&)(_Other.Parent)), Children((Vector<Entity>&&)(_Other.Children)), Camera((SafePointer<CameraComponent>&&)(_Other.Camera)), Light((SafePointer<LightComponent>&&)(_Other.Light)), Script((SafePointer<ScriptComponent>&&)(_Other.Script))
{
	SafePointer<Entity>::MoveAll(this, &_Other);

	_Other.CurrentScene = nullptr;
	_Other.GUID = GUID::GetString();
	_Other.Name = BFW_STRING_PREFIX("Name");
}

BFW::ECS::Entity::~Entity()
{
	SafePointer<Entity>::ReleaseAll(this);

	RemoveCameraComponent();
	RemoveLightComponent();
	RemoveScriptComponent();
	GUID::ReleaseString(GUID);
}

const bool BFW::ECS::Entity::Deserialize(const Assets::Json& _Json)
{
	*this = Entity();

	if (_Json.GetType() != Assets::_ObjectJsonType)
	{
		return false;
	}

	const Assets::JsonObjectData& _ObjectData = _Json.GetObjectData();

	if (_ObjectData.Tags.GetSize() != _ObjectData.Object.GetSize())
	{
		return false;
	}

	for (size_t _Index = 0; _Index < _ObjectData.Tags.GetSize(); _Index++)
	{
		if (_ObjectData.Tags[_Index] == "GUID")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_StringJsonType)
			{
				*this = Entity();
				return false;
			}

			bool _Error = false;

			GUID::ReleaseString(GUID);
			GUID = BFW_UTF8_TO_MACHINE(_ObjectData.Object[_Index].GetString(), &_Error);

			if (_Error || !GUID.size())
			{
				*this = Entity();
				return false;
			}

			uint64_t _GUID = 0;
			BFW_STRING_STREAM_TYPE _Stream(GUID);
			_Stream.imbue(std::locale::classic());

			if (!(_Stream >> _GUID) || !_Stream.eof())
			{
				*this = Entity();
				return false;
			}

			if (GUID::Reserve(_GUID))
			{
				continue;
			}

			BFW_STRING_TYPE _NewGUID = GUID::GetString();

			GUID = _NewGUID;

			continue;
		}

		if (_ObjectData.Tags[_Index] == "Name")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_StringJsonType)
			{
				*this = Entity();
				return false;
			}

			bool _Error = false;

			Name = BFW_UTF8_TO_MACHINE(_ObjectData.Object[_Index].GetString(), &_Error);

			if (_Error || !Name.size())
			{
				*this = Entity();
				return false;
			}

			continue;
		}

		if (_ObjectData.Tags[_Index] == "TagsList")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_ArrayJsonType)
			{
				*this = Entity();
				return false;
			}

			const Vector<Assets::Json>& _TagsList = _ObjectData.Object[_Index].GetArray();

			for (size_t _TagIndex = 0; _TagIndex < _TagsList.GetSize(); _TagIndex++)
			{
				if (_TagsList[_TagIndex].GetType() != Assets::_StringJsonType)
				{
					*this = Entity();
					return false;
				}

				bool _Error = false;

				AddTag(BFW_UTF8_TO_MACHINE(_TagsList[_TagIndex].GetString(), &_Error));

				if (_Error)
				{
					*this = Entity();
					return false;
				}
			}

			continue;
		}

		if (_ObjectData.Tags[_Index] == "Transform")
		{
			if (!Transform.Deserialize(_ObjectData.Object[_Index]))
			{
				*this = Entity();
				return false;
			}

			continue;
		}

		if (_ObjectData.Tags[_Index] == "Camera" && CurrentScene)
		{
			if (!AddCameraComponent().Deserialize(_ObjectData.Object[_Index]))
			{
				*this = Entity();
				return false;
			}

			continue;
		}

		if (_ObjectData.Tags[_Index] == "Light" && CurrentScene)
		{
			if (!AddLightComponent().Deserialize(_ObjectData.Object[_Index]))
			{
				*this = Entity();
				return false;
			}

			continue;
		}

		if (_ObjectData.Tags[_Index] == "Script" && CurrentScene)
		{
			if (!AddScriptComponent().Deserialize(_ObjectData.Object[_Index]))
			{
				*this = Entity();
				return false;
			}

			continue;
		}

		if (_ObjectData.Tags[_Index] == "Children")
		{
			if (_ObjectData.Object[_Index].GetType() != Assets::_ArrayJsonType)
			{
				*this = Entity();
				return false;
			}

			const Vector<Assets::Json>& _Children = _ObjectData.Object[_Index].GetArray();

			for (size_t _ChildIndex = 0; _ChildIndex < _Children.GetSize(); _ChildIndex++)
			{
				if (!EmplaceChild(Entity()).Deserialize(_Children[_ChildIndex]))
				{
					*this = Entity();
					return false;
				}
			}

			continue;
		}
	}

	return true;
}

void BFW::ECS::Entity::SetCurrentScene(Scene* _CurrentScene)
{
	if (CurrentScene == _CurrentScene)
	{
		return;
	}

	bool _HasCameraComponent = (CameraComponent*)(Camera) != nullptr;
	CameraComponent _Camera;
	bool _HasLightComponent = (LightComponent*)(Light) != nullptr;
	LightComponent _Light;
	bool _HasScriptComponent = (ScriptComponent*)(Script) != nullptr;
	ScriptComponent _Script;

	if (_HasCameraComponent)
	{
		_Camera = *Camera;
	}

	if (_HasLightComponent)
	{
		_Light = *Light;
	}

	if (_HasScriptComponent)
	{
		_Script = *Script;
	}

	RemoveCameraComponent();
	RemoveLightComponent();
	RemoveScriptComponent();

	CurrentScene = _CurrentScene;

	if (_HasCameraComponent)
	{
		AddCameraComponent(_Camera);
	}

	if (_HasLightComponent)
	{
		AddLightComponent(_Light);
	}

	if (_HasScriptComponent)
	{
		AddScriptComponent(_Script);
	}

	Parent = nullptr;

	for (size_t _Index = 0; _Index < Children.GetSize(); _Index++)
	{
		Children[_Index].SetCurrentScene(_CurrentScene);
		Children[_Index].Parent = this;
	}
}

const bool BFW::ECS::Entity::SetName(const BFW_STRING_VIEW_TYPE& _Name)
{
	if (!_Name.size())
	{
		return false;
	}

	Name = _Name;

	return true;
}

void BFW::ECS::Entity::AddTag(const BFW_STRING_VIEW_TYPE& _Tag)
{
	if (_Tag.size() == 0)
	{
		return;
	}

	for (size_t _Index = 0; _Index < TagsList.GetSize(); _Index++)
	{
		if (TagsList[_Index] == _Tag)
		{
			return;
		}
	}

	TagsList.EmplaceBack(BFW_STRING_TYPE(_Tag));
	Tags.Push(BFW_STRING_TYPE(_Tag).c_str(), true);
}

void BFW::ECS::Entity::RemoveTag(const BFW_STRING_VIEW_TYPE& _Tag)
{
	if (_Tag.size() == 0)
	{
		return;
	}

	Tags.Erase(BFW_STRING_TYPE(_Tag).c_str());

	for (size_t _Index = 0; _Index < TagsList.GetSize(); _Index++)
	{
		if (TagsList[_Index] == _Tag)
		{
			TagsList.Erase(_Index);
			return;
		}
	}
}

void BFW::ECS::Entity::ClearTags()
{
	TagsList.Clear();
	Tags = Trie<bool>();
}

void BFW::ECS::Entity::SetParent(Entity* _Parent)
{
	if (_Parent == this || (_Parent != nullptr && CurrentScene != _Parent->CurrentScene))
	{
		throw nullptr;
	}

	Entity* _Current = _Parent;

	while (_Current)
	{
		if (_Current == this)
		{
			throw nullptr;
		}

		_Current = (Entity*)(_Current->Parent);
	}

	Parent = _Parent;
}

BFW::ECS::Entity& BFW::ECS::Entity::PushChild(const Entity& _Child)
{
	Children.PushBack(_Child).SetCurrentScene(CurrentScene);
	Children[Children.GetSize() - 1].Parent = this;
	return Children[Children.GetSize() - 1];
}

BFW::ECS::Entity& BFW::ECS::Entity::EmplaceChild(Entity&& _Child)
{
	Children.EmplaceBack((Entity&&)(_Child)).SetCurrentScene(CurrentScene);
	Children[Children.GetSize() - 1].Parent = this;
	return Children[Children.GetSize() - 1];
}

void BFW::ECS::Entity::EraseChild(const size_t _Index)
{
	Children.Erase(_Index);
}

void BFW::ECS::Entity::ClearChildren()
{
	Children.Clear();
}

BFW::ECS::CameraComponent& BFW::ECS::Entity::AddCameraComponent(const CameraComponent& _Component)
{
	if (!CurrentScene || !EntityAddComponent<CameraComponent>(CurrentScene->CameraComponents, Camera, _Component))
	{
		throw nullptr;
	}

	return *Camera;
}

BFW::ECS::LightComponent& BFW::ECS::Entity::AddLightComponent(const LightComponent& _Component)
{
	if (!CurrentScene || !EntityAddComponent<LightComponent>(CurrentScene->LightComponents, Light, _Component))
	{
		throw nullptr;
	}

	return *Light;
}

BFW::ECS::ScriptComponent& BFW::ECS::Entity::AddScriptComponent(const ScriptComponent& _Component)
{
	if (!CurrentScene || !EntityAddComponent<ScriptComponent>(CurrentScene->ScriptComponents, Script, _Component))
	{
		throw nullptr;
	}

	return *Script;
}

void BFW::ECS::Entity::RemoveCameraComponent()
{
	bool _Removed = !CurrentScene || !(CameraComponent*)(Camera) || EntityRemoveComponent<CameraComponent>(CurrentScene->CameraComponents, Camera);
}

void BFW::ECS::Entity::RemoveLightComponent()
{
	bool _Removed = !CurrentScene || !(LightComponent*)(Light) || EntityRemoveComponent<LightComponent>(CurrentScene->LightComponents, Light);
}

void BFW::ECS::Entity::RemoveScriptComponent()
{
	bool _Removed = !CurrentScene || !(ScriptComponent*)(Script) || EntityRemoveComponent<ScriptComponent>(CurrentScene->ScriptComponents, Script);
}

const BFW::Assets::Json BFW::ECS::Entity::Serialize() const
{
	Assets::Json _Result;

	_Result.SetObject();

	Assets::JsonObjectData& _ObjectData = _Result.GetObjectData();

	bool _Error = false;

	_ObjectData.Tags.PushBack("GUID");
	_ObjectData.Object.PushBack(Assets::Json()).SetString(BFW_MACHINE_TO_UTF8(GUID, &_Error));

	if (_Error)
	{
		return Assets::Json();
	}

	_ObjectData.Tags.PushBack("Name");
	_ObjectData.Object.PushBack(Assets::Json()).SetString(BFW_MACHINE_TO_UTF8(Name, &_Error));

	if (_Error)
	{
		return Assets::Json();
	}

	_ObjectData.Tags.PushBack("TagsList");
	_ObjectData.Object.PushBack(Assets::Json()).SetArray();
	Vector<Assets::Json>& _TagsList = _ObjectData.Object[_ObjectData.Object.GetSize() - 1].GetArray();

	for (size_t _Index = 0; _Index < TagsList.GetSize(); _Index++)
	{
		_TagsList.PushBack(Assets::Json()).SetString(BFW_MACHINE_TO_UTF8(TagsList[_Index], &_Error));

		if (_Error)
		{
			return Assets::Json();
		}
	}

	_ObjectData.Tags.PushBack("Transform");
	_ObjectData.Object.PushBack(Transform.Serialize());

	if ((const CameraComponent*)(Camera))
	{
		_ObjectData.Tags.PushBack("Camera");
		_ObjectData.Object.PushBack(Camera->Serialize());
	}

	if ((const LightComponent*)(Light))
	{
		_ObjectData.Tags.PushBack("Light");
		_ObjectData.Object.PushBack(Light->Serialize());
	}

	if ((const ScriptComponent*)(Script))
	{
		_ObjectData.Tags.PushBack("Script");
		_ObjectData.Object.PushBack(Script->Serialize());
	}

	if (!Children.GetSize())
	{
		return _Result;
	}

	_ObjectData.Tags.PushBack("Children");
	_ObjectData.Object.PushBack(Assets::Json()).SetArray();
	Vector<Assets::Json>& _Children = _ObjectData.Object[_ObjectData.Object.GetSize() - 1].GetArray();

	for (size_t _Index = 0; _Index < Children.GetSize(); _Index++)
	{
		if (_Children.PushBack(Children[_Index].Serialize()).GetType() == Assets::_NullJsonType)
		{
			return Assets::Json();
		}
	}

	return _Result;
}

const bool BFW::ECS::Entity::HasTag(const BFW_STRING_VIEW_TYPE& _Tag) const
{
	return Tags.GetData(BFW_STRING_TYPE(_Tag).c_str()) != nullptr;
}

BFW::ECS::Scene* BFW::ECS::Entity::GetCurrentScene()
{
	return CurrentScene;
}

const BFW::ECS::Scene* BFW::ECS::Entity::GetCurrentScene() const
{
	return CurrentScene;
}

const BFW_STRING_TYPE& BFW::ECS::Entity::GetGUID() const
{
	return GUID;
}

const BFW_STRING_TYPE& BFW::ECS::Entity::GetName() const
{
	return Name;
}

const BFW::Vector<BFW_STRING_TYPE>& BFW::ECS::Entity::GetTagsList() const
{
	return TagsList;
}

BFW::ECS::Entity* BFW::ECS::Entity::GetParent()
{
	return (Entity*)(Parent);
}

const BFW::ECS::Entity* BFW::ECS::Entity::GetParent() const
{
	return (const Entity*)(Parent);
}

const size_t BFW::ECS::Entity::GetChildrenSize() const
{
	return Children.GetSize();
}

BFW::ECS::Entity& BFW::ECS::Entity::GetChild(const size_t _Index)
{
	return Children[_Index];
}

const BFW::ECS::Entity& BFW::ECS::Entity::GetChild(const size_t _Index) const
{
	return Children[_Index];
}

BFW::SafePointer<BFW::ECS::CameraComponent> BFW::ECS::Entity::GetCamera()
{
	return Camera;
}

const BFW::SafePointer<BFW::ECS::CameraComponent> BFW::ECS::Entity::GetCamera() const
{
	return Camera;
}

BFW::SafePointer<BFW::ECS::LightComponent> BFW::ECS::Entity::GetLight()
{
	return Light;
}

const BFW::SafePointer<BFW::ECS::LightComponent> BFW::ECS::Entity::GetLight() const
{
	return Light;
}

BFW::SafePointer<BFW::ECS::ScriptComponent> BFW::ECS::Entity::GetScript()
{
	return Script;
}

const BFW::SafePointer<BFW::ECS::ScriptComponent> BFW::ECS::Entity::GetScript() const
{
	return Script;
}

BFW::ECS::Entity& BFW::ECS::Entity::operator= (const Entity& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	RemoveCameraComponent();
	RemoveLightComponent();
	RemoveScriptComponent();
	GUID::ReleaseString(GUID);

	Transform = _Other.Transform;
	CurrentScene = _Other.CurrentScene;
	GUID = GUID::GetString();
	Name = _Other.Name;
	TagsList = _Other.TagsList;
	Tags = _Other.Tags;
	Parent = nullptr;
	Children = _Other.Children;

	for (size_t _Index = 0; _Index < Children.GetSize(); _Index++)
	{
		Children[_Index].Parent = this;
	}

	if (!CurrentScene)
	{
		return *this;
	}

	if ((const CameraComponent*)(_Other.Camera))
	{
		AddCameraComponent(*_Other.Camera);
	}

	if ((const LightComponent*)(_Other.Light))
	{
		AddLightComponent(*_Other.Light);
	}

	if ((const ScriptComponent*)(_Other.Script))
	{
		AddScriptComponent(*_Other.Script);
	}

	return *this;
}

BFW::ECS::Entity& BFW::ECS::Entity::operator= (Entity&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	RemoveCameraComponent();
	RemoveLightComponent();
	RemoveScriptComponent();
	GUID::ReleaseString(GUID);

	SafePointer<Entity>::MoveAll(this, &_Other);

	Transform = (TransformComponent&&)(_Other.Transform);
	CurrentScene = _Other.CurrentScene;
	GUID = _Other.GUID;
	Name = _Other.Name;
	TagsList = (Vector<BFW_STRING_TYPE>&&)(_Other.TagsList);
	Tags = (Trie<bool>&&)(_Other.Tags);
	Parent = (SafePointer<Entity>&&)(_Other.Parent);
	Children = (Vector<Entity>&&)(_Other.Children);
	Camera = (SafePointer<CameraComponent>&&)(_Other.Camera);
	Light = (SafePointer<LightComponent>&&)(_Other.Light);
	Script = (SafePointer<ScriptComponent>&&)(_Other.Script);

	_Other.CurrentScene = nullptr;
	_Other.GUID = GUID::GetString();
	_Other.Name = BFW_STRING_PREFIX("Name");

	return *this;
}



BFW::ECS::Scene::Scene() : GUID(GUID::GetString()), Name(BFW_STRING_PREFIX("Name")), Entities(), CameraComponents(), LightComponents(), ScriptComponents(), SpawnQueue(), DespawnQueue(), ActiveCamera(nullptr)
{

}

BFW::ECS::Scene::Scene(const Scene& _Other) : GUID(GUID::GetString()), Name(_Other.Name), Entities(_Other.Entities), CameraComponents(), LightComponents(), ScriptComponents(), SpawnQueue(_Other.SpawnQueue), DespawnQueue(), ActiveCamera(nullptr)
{
	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		Entities[_Index].SetCurrentScene(this);
	}

	for (size_t _Index = 0; _Index < SpawnQueue.GetSize(); _Index++)
	{
		SpawnQueue[_Index].SetCurrentScene(this);
	}

	Vector<Entity*> _Queue;
	Vector<const Entity*> _OldQueue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);
		_OldQueue.PushBack(&_Other.Entities[_Index]);

		while (_Queue.GetSize())
		{
			Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			const Entity* _OldCurrent = _OldQueue[_OldQueue.GetSize() - 1];
			_OldQueue.Erase(_OldQueue.GetSize() - 1);

			for (size_t _SpawnIndex = 0; _SpawnIndex < _Other.SpawnQueue.GetSize(); _SpawnIndex++)
			{
				if (_OldCurrent == _Other.SpawnQueue[_SpawnIndex].GetParent())
				{
					SpawnQueue[_SpawnIndex].SetParent(_Current);
				}
			}

			for (size_t _DespawnIndex = 0; _DespawnIndex < _Other.DespawnQueue.GetSize(); _DespawnIndex++)
			{
				if (_OldCurrent == (const Entity*)(_Other.DespawnQueue[_DespawnIndex]))
				{
					DespawnQueue.PushBack(_Current);
					break;
				}
			}

			if ((const CameraComponent*)(_Other.ActiveCamera) != nullptr && (const CameraComponent*)(_Other.ActiveCamera) == (const CameraComponent*)(_OldCurrent->GetCamera()))
			{
				ActiveCamera = _Current->GetCamera();
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Child));
				_OldQueue.PushBack(&_OldCurrent->GetChild(_Child));
			}
		}
	}
}

BFW::ECS::Scene::Scene(Scene&& _Other) noexcept : GUID(_Other.GUID), Name(_Other.Name), Entities((Vector<Entity>&&)(_Other.Entities)), CameraComponents(), LightComponents(), ScriptComponents(), SpawnQueue((Vector<Entity>&&)(_Other.SpawnQueue)), DespawnQueue((Vector<SafePointer<Entity>>&&)(_Other.DespawnQueue)), ActiveCamera((SafePointer<CameraComponent>)(_Other.ActiveCamera))
{
	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		Entities[_Index].SetCurrentScene(this);
	}

	for (size_t _Index = 0; _Index < SpawnQueue.GetSize(); _Index++)
	{
		SpawnQueue[_Index].SetCurrentScene(this);
	}

	_Other.GUID = GUID::GetString();
	_Other.Name = BFW_STRING_PREFIX("Name");
}

BFW::ECS::Scene::~Scene()
{
	Clear();
	GUID::ReleaseString(GUID);
}

const bool BFW::ECS::Scene::Deserialize(const Assets::Json& _Json)
{
	*this = Scene();

	if (_Json.GetType() != Assets::_ArrayJsonType || !_Json.GetArray().GetSize() || _Json.GetArray()[0].GetType() != Assets::_ObjectJsonType)
	{
		return false;
	}

	const Assets::JsonObjectData& _SceneData = _Json.GetArray()[0].GetObjectData();

	if (_SceneData.Tags.GetSize() != _SceneData.Object.GetSize())
	{
		return false;
	}

	for (size_t _Index = 0; _Index < _SceneData.Tags.GetSize(); _Index++)
	{
		if (_SceneData.Tags[_Index] == "GUID")
		{
			if (_SceneData.Object[_Index].GetType() != Assets::_StringJsonType)
			{
				*this = Scene();
				return false;
			}

			bool _Error = false;

			GUID::ReleaseString(GUID);
			GUID = BFW_UTF8_TO_MACHINE(_SceneData.Object[_Index].GetString(), &_Error);

			if (_Error || !GUID.size())
			{
				*this = Scene();
				return false;
			}

			uint64_t _GUID = 0;
			BFW_STRING_STREAM_TYPE _Stream(GUID);
			_Stream.imbue(std::locale::classic());

			if (!(_Stream >> _GUID) || !_Stream.eof())
			{
				*this = Scene();
				return false;
			}

			if (GUID::Reserve(_GUID))
			{
				continue;
			}

			BFW_STRING_TYPE _NewGUID = GUID::GetString();

			GUID = _NewGUID;

			continue;
		}

		if (_SceneData.Tags[_Index] == "Name")
		{
			if (_SceneData.Object[_Index].GetType() != Assets::_StringJsonType)
			{
				*this = Scene();
				return false;
			}

			bool _Error = false;

			Name = BFW_UTF8_TO_MACHINE(_SceneData.Object[_Index].GetString(), &_Error);

			if (_Error || !Name.size())
			{
				*this = Scene();
				return false;
			}

			continue;
		}
	}

	const Vector<Assets::Json>& _Entities = _Json.GetArray();

	for (size_t _Index = 1; _Index < _Entities.GetSize(); _Index++)
	{
		Entity& _Entity = Entities.EmplaceBack(Entity());
		_Entity.SetCurrentScene(this);

		if (!_Entity.Deserialize(_Entities[_Index]))
		{
			*this = Scene();
			return false;
		}
	}

	return true;
}

const bool BFW::ECS::Scene::Setup(RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager)
{
	Vector<Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if ((ScriptComponent*)(_Current->GetScript()) != nullptr && _Current->GetScript()->GetScriptLibName().size() != 0)
			{
#ifdef BFW_WINDOWS_PLATFORM

				size_t _Id = 0;
				BFW_STRING_STREAM_TYPE _Stream(_Current->GetScript()->GetScriptLibName());
				_Stream.imbue(std::locale::classic());

				if ((_Stream >> _Id) && _Stream.eof())
				{
					_Manager.QueueResourceScriptLib(_Id);
				}
				else
				{
					_Manager.QueueScriptLib(_Current->GetScript()->GetScriptLibName().c_str());
				}

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

				_Manager.QueueScriptLib(_Current->GetScript()->GetScriptLibName().c_str());

#endif
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Current->GetChildrenSize() - 1 - _Child));
			}
		}
	}

	if (!_Manager.Flush())
	{
		return false;
	}

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if ((ScriptComponent*)(_Current->GetScript()) != nullptr && _Current->GetScript()->GetScriptLibName().size() != 0)
			{
				_Current->GetScript()->SetScript(_Current->GetScript()->GetScriptLibName(), _Manager.GetScriptLib(_Current->GetScript()->GetScriptLibName().c_str()), _Current->GetScript()->GetNameSpace());
				_Current->GetScript()->OnSetup(*_Current, _Application, _Menu, _Manager, *this);
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Current->GetChildrenSize() - 1 - _Child));
			}
		}
	}

	return true;
}

void BFW::ECS::Scene::Update(RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager)
{
	Vector<Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if ((ScriptComponent*)(_Current->GetScript()) != nullptr)
			{
				_Current->GetScript()->OnUpdate(*_Current, _Application, _Menu, _Manager, *this);
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Current->GetChildrenSize() - 1 - _Child));
			}
		}
	}
}

void BFW::ECS::Scene::LateUpdate(RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager)
{
	Vector<Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if ((ScriptComponent*)(_Current->GetScript()) != nullptr)
			{
				_Current->GetScript()->OnLateUpdate(*_Current, _Application, _Menu, _Manager, *this);
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Current->GetChildrenSize() - 1 - _Child));
			}
		}
	}

	while (DespawnQueue.GetSize())
	{
		size_t _DespawnIndex = 0;

		if ((Entity*)(DespawnQueue[_DespawnIndex]) == nullptr)
		{
			DespawnQueue.Erase(_DespawnIndex);
			continue;
		}

		if (!DespawnQueue[_DespawnIndex]->GetParent())
		{
			for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
			{
				if ((Entity*)(DespawnQueue[_DespawnIndex]) != &Entities[_Index])
				{
					continue;
				}

				_Queue.PushBack(&Entities[_Index]);

				while (_Queue.GetSize())
				{
					Entity* _Current = _Queue[_Queue.GetSize() - 1];
					_Queue.Erase(_Queue.GetSize() - 1);

					if ((ScriptComponent*)(_Current->GetScript()) != nullptr)
					{
						_Current->GetScript()->OnStop(*_Current, _Application, _Menu, _Manager, *this);
					}

					for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
					{
						_Queue.PushBack(&_Current->GetChild(_Current->GetChildrenSize() - 1 - _Child));
					}
				}

				Entities.Erase(_Index);
				break;
			}

			DespawnQueue.Erase(_DespawnIndex);
			continue;
		}

		Entity* _Parent = DespawnQueue[_DespawnIndex]->GetParent();

		for (size_t _Index = 0; _Index < _Parent->GetChildrenSize(); _Index++)
		{
			if ((Entity*)(DespawnQueue[_DespawnIndex]) != &_Parent->GetChild(_Index))
			{
				continue;
			}

			_Queue.PushBack((Entity*)(DespawnQueue[_DespawnIndex]));

			while (_Queue.GetSize())
			{
				Entity* _Current = _Queue[_Queue.GetSize() - 1];
				_Queue.Erase(_Queue.GetSize() - 1);

				if ((ScriptComponent*)(_Current->GetScript()) != nullptr)
				{
					_Current->GetScript()->OnStop(*_Current, _Application, _Menu, _Manager, *this);
				}

				for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
				{
					_Queue.PushBack(&_Current->GetChild(_Current->GetChildrenSize() - 1 - _Child));
				}
			}

			_Parent->EraseChild(_Index);
			break;
		}

		DespawnQueue.Erase(_DespawnIndex);
	}

	DespawnQueue.Clear();

	for (size_t _SpawnIndex = 0; _SpawnIndex < SpawnQueue.GetSize(); _SpawnIndex++)
	{
		if (!SpawnQueue[_SpawnIndex].GetParent())
		{
			Entities.EmplaceBack((Entity&&)(SpawnQueue[_SpawnIndex]));
			continue;
		}

		Entity* _Parent = SpawnQueue[_SpawnIndex].GetParent();

		_Parent->EmplaceChild((Entity&&)(SpawnQueue[_SpawnIndex]));
	}

	SpawnQueue.Clear();
}

void BFW::ECS::Scene::FixedUpdate(RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager)
{
	Vector<Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if ((ScriptComponent*)(_Current->GetScript()) != nullptr)
			{
				_Current->GetScript()->OnFixedUpdate(*_Current, _Application, _Menu, _Manager, *this);
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Current->GetChildrenSize() - 1 - _Child));
			}
		}
	}
}

void BFW::ECS::Scene::Render(RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager)
{
	Vector<Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if ((ScriptComponent*)(_Current->GetScript()) != nullptr)
			{
				_Current->GetScript()->OnRender(*_Current, _Application, _Menu, _Manager, *this);
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Current->GetChildrenSize() - 1 - _Child));
			}
		}
	}
}

void BFW::ECS::Scene::Stop(RunTime::Application& _Application, RunTime::Menu& _Menu, Assets::Manager& _Manager)
{
	Vector<Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if ((ScriptComponent*)(_Current->GetScript()) != nullptr)
			{
				_Current->GetScript()->OnStop(*_Current, _Application, _Menu, _Manager, *this);
				_Current->GetScript()->SetScript(_Current->GetScript()->GetScriptLibName(), SharedPointer<Assets::ScriptLib>(), _Current->GetScript()->GetNameSpace());
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Current->GetChildrenSize() - 1 - _Child));
			}
		}
	}

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if ((ScriptComponent*)(_Current->GetScript()) != nullptr && _Current->GetScript()->GetScriptLibName().size() != 0)
			{
#ifdef BFW_WINDOWS_PLATFORM

				size_t _Id = 0;
				BFW_STRING_STREAM_TYPE _Stream(_Current->GetScript()->GetScriptLibName());
				_Stream.imbue(std::locale::classic());

				if ((_Stream >> _Id) && _Stream.eof())
				{
					_Manager.ReleaseResourceScriptLib(_Id);
				}
				else
				{
					_Manager.ReleaseScriptLib(_Current->GetScript()->GetScriptLibName().c_str());
				}

#endif

#if defined BFW_LINUX_PLATFORM || defined BFW_ESP32_PLATFORM

				_Manager.ReleaseScriptLib(_Current->GetScript()->GetScriptLibName().c_str());

#endif
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Current->GetChildrenSize() - 1 - _Child));
			}
		}
	}
}

BFW::ECS::Entity& BFW::ECS::Scene::Add(Entity* _Parent)
{
	if (_Parent && _Parent->GetCurrentScene() != this)
	{
		throw nullptr;
	}

	Entity& _NewEntity = SpawnQueue.EmplaceBack(Entity());

	_NewEntity.SetCurrentScene(this);
	_NewEntity.SetParent(_Parent);

	return _NewEntity;
}

BFW::ECS::Entity& BFW::ECS::Scene::Add(const Entity& _Entity, Entity* _Parent)
{
	if (_Parent && _Parent->GetCurrentScene() != this)
	{
		throw nullptr;
	}

	Entity& _NewEntity = SpawnQueue.EmplaceBack(Entity());

	_NewEntity = _Entity;
	_NewEntity.SetCurrentScene(this);
	_NewEntity.SetParent(_Parent);

	return _NewEntity;
}

BFW::ECS::Entity& BFW::ECS::Scene::Add(Entity&& _Entity, Entity* _Parent)
{
	if (_Parent && _Parent->GetCurrentScene() != this)
	{
		throw nullptr;
	}

	Entity& _NewEntity = SpawnQueue.EmplaceBack(Entity());

	_NewEntity = (Entity&&)(_Entity);
	_NewEntity.SetCurrentScene(this);
	_NewEntity.SetParent(_Parent);

	return _NewEntity;
}

BFW::ECS::Entity* BFW::ECS::Scene::AddPrefab(const Assets::Json& _Json, Entity* _Parent)
{
	if (_Parent && _Parent->GetCurrentScene() != this)
	{
		throw nullptr;
	}

	Entity& _NewEntity = SpawnQueue.EmplaceBack(Entity());

	_NewEntity.SetCurrentScene(this);
	_NewEntity.SetParent(_Parent);

	if (!_NewEntity.Deserialize(_Json))
	{
		SpawnQueue.Erase(SpawnQueue.GetSize() - 1);
		return nullptr;
	}

	return &SpawnQueue[SpawnQueue.GetSize() - 1];
}

void BFW::ECS::Scene::Remove(const size_t _Index)
{
	DespawnQueue.EmplaceBack(SafePointer<Entity>(&Entities[_Index]));
}

void BFW::ECS::Scene::Remove(const BFW_STRING_VIEW_TYPE& _GUID)
{
	DespawnQueue.EmplaceBack(SafePointer<Entity>(Find(_GUID)));
}

void BFW::ECS::Scene::Remove(const Entity* _Entity)
{
	DespawnQueue.EmplaceBack(SafePointer<Entity>((Entity*)(_Entity)));
}

void BFW::ECS::Scene::Clear()
{
	Entities.Clear();
	CameraComponents.Clear();
	LightComponents.Clear();
	ScriptComponents.Clear();
	SpawnQueue.Clear();
	DespawnQueue.Clear();
}

const bool BFW::ECS::Scene::SetName(const BFW_STRING_VIEW_TYPE& _Name)
{
	if (!_Name.size())
	{
		return false;
	}

	Name = _Name;

	return true;
}

void BFW::ECS::Scene::SetActiveCamera(const CameraComponent* _ActiveCamera)
{
	if (!_ActiveCamera)
	{
		ActiveCamera = nullptr;
		return;
	}

	for (size_t _Index = 0; _Index < CameraComponents.GetSize(); _Index++)
	{
		if (_ActiveCamera == &CameraComponents[_Index])
		{
			ActiveCamera = (CameraComponent*)(_ActiveCamera);
			return;
		}
	}

	throw nullptr;
}

const BFW::Assets::Json BFW::ECS::Scene::Serialize() const
{
	Assets::Json _Result;

	_Result.SetArray();

	Vector<Assets::Json>& _Array = _Result.GetArray();

	_Array.EmplaceBack(Assets::Json()).SetObject();
	Assets::JsonObjectData& _SceneData = _Array[0].GetObjectData();

	bool _Error = false;

	_SceneData.Tags.PushBack("GUID");
	_SceneData.Object.PushBack(Assets::Json()).SetString(BFW_MACHINE_TO_UTF8(GUID, &_Error));

	if (_Error)
	{
		return Assets::Json();
	}

	_SceneData.Tags.PushBack("Name");
	_SceneData.Object.PushBack(Assets::Json()).SetString(BFW_MACHINE_TO_UTF8(Name, &_Error));

	if (_Error)
	{
		return Assets::Json();
	}

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		if (_Array.PushBack(Entities[_Index].Serialize()).GetType() == Assets::_NullJsonType)
		{
			return Assets::Json();
		}
	}

	return _Result;
}

BFW::ECS::Entity* BFW::ECS::Scene::Find(const BFW_STRING_VIEW_TYPE& _GUID)
{
	if (!_GUID.size())
	{
		return nullptr;
	}

	Vector<Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if (_Current->GetGUID() == _GUID)
			{
				return _Current;
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Child));
			}
		}
	}

	return nullptr;
}

const BFW::ECS::Entity* BFW::ECS::Scene::Find(const BFW_STRING_VIEW_TYPE& _GUID) const
{
	if (!_GUID.size())
	{
		return nullptr;
	}

	Vector<const Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			const Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if (_Current->GetGUID() == _GUID)
			{
				return _Current;
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Child));
			}
		}
	}

	return nullptr;
}

BFW::ECS::Entity* BFW::ECS::Scene::FindByName(const BFW_STRING_VIEW_TYPE& _Name)
{
	if (!_Name.size())
	{
		return nullptr;
	}

	Vector<Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if (_Current->GetName() == _Name)
			{
				return _Current;
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Child));
			}
		}
	}

	return nullptr;
}

const BFW::ECS::Entity* BFW::ECS::Scene::FindByName(const BFW_STRING_VIEW_TYPE& _Name) const
{
	if (!_Name.size())
	{
		return nullptr;
	}

	Vector<const Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			const Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if (_Current->GetName() == _Name)
			{
				return _Current;
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Child));
			}
		}
	}

	return nullptr;
}

const BFW::Vector<BFW::ECS::Entity*> BFW::ECS::Scene::FindByTag(const BFW_STRING_VIEW_TYPE& _Tag)
{
	if (!_Tag.size())
	{
		return Vector<Entity*>();
	}

	Vector<Entity*> _Result;

	Vector<Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if (_Current->HasTag(_Tag))
			{
				_Result.PushBack(_Current);
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Child));
			}
		}
	}

	return _Result;
}

const BFW::Vector<const BFW::ECS::Entity*> BFW::ECS::Scene::FindByTag(const BFW_STRING_VIEW_TYPE& _Tag) const
{
	if (!_Tag.size())
	{
		return Vector<const Entity*>();
	}

	Vector<const Entity*> _Result;

	Vector<const Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			const Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if (_Current->HasTag(_Tag))
			{
				_Result.PushBack(_Current);
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Child));
			}
		}
	}

	return _Result;
}

const bool BFW::ECS::Scene::Contains(const Entity* _Entity) const
{
	if (!_Entity)
	{
		return false;
	}

	Vector<const Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			const Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if (_Current == _Entity)
			{
				return true;
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Child));
			}
		}
	}

	return false;
}

const bool BFW::ECS::Scene::Contains(const BFW_STRING_VIEW_TYPE& _GUID) const
{
	if (!_GUID.size())
	{
		return false;
	}

	Vector<const Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			const Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			if (_Current->GetGUID() == _GUID)
			{
				return true;
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Child));
			}
		}
	}

	return false;
}

const BFW_STRING_TYPE& BFW::ECS::Scene::GetGUID() const
{
	return GUID;
}

const BFW_STRING_TYPE& BFW::ECS::Scene::GetName() const
{
	return Name;
}

BFW::ECS::CameraComponent* BFW::ECS::Scene::GetActiveCamera()
{
	return (CameraComponent*)(ActiveCamera);
}

const BFW::ECS::CameraComponent* BFW::ECS::Scene::GetActiveCamera() const
{
	return (const CameraComponent*)(ActiveCamera);
}

const size_t BFW::ECS::Scene::GetTotalCount() const
{
	size_t _Size = 0;

	Vector<const Entity*> _Queue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);

		while (_Queue.GetSize())
		{
			const Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			_Size++;

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Current->GetChildrenSize() - 1 - _Child));
			}
		}
	}

	return _Size;
}

const size_t BFW::ECS::Scene::GetRootCount() const
{
	return Entities.GetSize();
}

BFW::ECS::Entity& BFW::ECS::Scene::GetEntity(const size_t _Index)
{
	return Entities[_Index];
}

const BFW::ECS::Entity& BFW::ECS::Scene::GetEntity(const size_t _Index) const
{
	return Entities[_Index];
}

BFW::ECS::Scene& BFW::ECS::Scene::operator= (const Scene& _Other)
{
	if (this == &_Other)
	{
		return *this;
	}

	Clear();
	GUID::ReleaseString(GUID);

	GUID = GUID::GetString();
	Name = _Other.Name;
	Entities = _Other.Entities;
	SpawnQueue = _Other.SpawnQueue;
	ActiveCamera = nullptr;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		Entities[_Index].SetCurrentScene(this);
	}

	for (size_t _Index = 0; _Index < SpawnQueue.GetSize(); _Index++)
	{
		SpawnQueue[_Index].SetCurrentScene(this);
	}

	Vector<Entity*> _Queue;
	Vector<const Entity*> _OldQueue;

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		_Queue.PushBack(&Entities[_Index]);
		_OldQueue.PushBack(&_Other.Entities[_Index]);

		while (_Queue.GetSize())
		{
			Entity* _Current = _Queue[_Queue.GetSize() - 1];
			_Queue.Erase(_Queue.GetSize() - 1);

			const Entity* _OldCurrent = _OldQueue[_OldQueue.GetSize() - 1];
			_OldQueue.Erase(_OldQueue.GetSize() - 1);

			for (size_t _SpawnIndex = 0; _SpawnIndex < _Other.SpawnQueue.GetSize(); _SpawnIndex++)
			{
				if (_OldCurrent == _Other.SpawnQueue[_SpawnIndex].GetParent())
				{
					SpawnQueue[_SpawnIndex].SetParent(_Current);
				}
			}

			for (size_t _DespawnIndex = 0; _DespawnIndex < _Other.DespawnQueue.GetSize(); _DespawnIndex++)
			{
				if (_OldCurrent == (const Entity*)(_Other.DespawnQueue[_DespawnIndex]))
				{
					DespawnQueue.PushBack(_Current);
					break;
				}
			}

			if ((const CameraComponent*)(_Other.ActiveCamera) != nullptr && (const CameraComponent*)(_Other.ActiveCamera) == (const CameraComponent*)(_OldCurrent->GetCamera()))
			{
				ActiveCamera = _Current->GetCamera();
			}

			for (size_t _Child = 0; _Child < _Current->GetChildrenSize(); _Child++)
			{
				_Queue.PushBack(&_Current->GetChild(_Child));
				_OldQueue.PushBack(&_OldCurrent->GetChild(_Child));
			}
		}
	}

	return *this;
}

BFW::ECS::Scene& BFW::ECS::Scene::operator= (Scene&& _Other) noexcept
{
	if (this == &_Other)
	{
		return *this;
	}

	Clear();
	GUID::ReleaseString(GUID);

	GUID = _Other.GUID;
	Name = _Other.Name;
	Entities = (Vector<Entity>&&)(_Other.Entities);
	SpawnQueue = (Vector<Entity>&&)(_Other.SpawnQueue);
	DespawnQueue = (Vector<SafePointer<Entity>>&&)(_Other.DespawnQueue);
	ActiveCamera = (SafePointer<CameraComponent>)(_Other.ActiveCamera);

	for (size_t _Index = 0; _Index < Entities.GetSize(); _Index++)
	{
		Entities[_Index].SetCurrentScene(this);
	}

	for (size_t _Index = 0; _Index < SpawnQueue.GetSize(); _Index++)
	{
		SpawnQueue[_Index].SetCurrentScene(this);
	}

	_Other.GUID = GUID::GetString();
	_Other.Name = BFW_STRING_PREFIX("Name");

	return *this;
}
