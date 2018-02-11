#include <octoon/transform_component.h>

namespace octoon
{
	OctoonImplementSubClass(TransformComponent, GameComponent, "TransformComponent")

	TransformComponent::TransformComponent() noexcept
		: local_scaling_(math::float3::One)
		, local_translate_(math::float3::Zero)
		, local_rotation_(math::Quaternion::Zero)
		, world_scaling_(math::float3::One)
		, world_translate_(math::float3::Zero)
		, world_rotation_(math::Quaternion::Zero)
		, local_need_updates_(true)
		, world_need_updates_(true)
	{
	}

	TransformComponent::~TransformComponent()
	{
	}

	void
	TransformComponent::set_translate(const math::float3& pos) noexcept
	{
		if (local_translate_ != pos)
		{
			this->on_move_before();

			local_translate_ = pos;
			local_need_updates_ = true;

			this->update_local_children();
			this->on_move_after();
		}
	}

	void
	TransformComponent::set_translateAccum(const math::float3& v) noexcept
	{
		this->set_translate(local_translate_ + v);
	}

	const math::float3&
	TransformComponent::get_translate() const noexcept
	{
		update_local_transform();
		return local_translate_;
	}

	void
	TransformComponent::set_scale(const math::float3& scale) noexcept
	{
		if (local_scaling_ != scale)
		{
			this->on_move_before();

			local_scaling_ = scale;
			local_need_updates_ = true;

			this->update_local_children();
			this->on_move_after();
		}
	}

	void
	TransformComponent::set_scale_all(const float scale) noexcept
	{
		this->set_scale(math::float3(scale, scale, scale));
	}

	void
	TransformComponent::set_scale_accum(const math::float3& scale) noexcept
	{
		this->set_scale(local_scaling_ + scale);
	}

	const math::float3&
	TransformComponent::get_scale() const noexcept
	{
		update_local_transform();
		return local_scaling_;
	}

	void
	TransformComponent::set_quaternion(const math::Quaternion& quat) noexcept
	{
		if (local_rotation_ != quat)
		{
			this->on_move_before();

			local_rotation_ = quat;
			local_need_updates_ = true;

			this->update_local_children();
			this->on_move_after();
		}
	}

	void
	TransformComponent::set_quaternion_accum(const math::Quaternion& quat) noexcept
	{
		this->set_quaternion(math::cross(quat, local_rotation_));
	}

	const math::Quaternion&
	TransformComponent::get_quaternion() const noexcept
	{
		update_local_transform();
		return local_rotation_;
	}

	const math::float3&
	TransformComponent::get_right() const noexcept
	{
		update_local_transform();
		return math::right(local_transform_);
	}

	const math::float3&
	TransformComponent::get_up() const noexcept
	{
		update_local_transform();
		return math::up(local_transform_);
	}

	const math::float3&
	TransformComponent::get_forward() const noexcept
	{
		update_local_transform();
		return math::forward(local_transform_);
	}

	void
	TransformComponent::set_transform(const math::float4x4& transform) noexcept
	{
		this->on_move_before();

		local_transform_ = transform.get_transform(local_translate_, local_rotation_, local_scaling_);
		local_need_updates_ = false;

		this->update_local_children();
		this->on_move_after();
	}

	void
	TransformComponent::set_transform_only_rotate(const math::float4x4& transform) noexcept
	{
		this->on_move_before();

		local_transform_ = transform.get_transform_without_scaler(local_translate_, local_rotation_);
		local_transform_.scale(local_scaling_);
		local_need_updates_ = false;

		this->update_local_children();
		this->on_move_after();
	}

	const math::float4x4&
	TransformComponent::get_transform() const noexcept
	{
		this->update_local_transform();
		return local_transform_;
	}

	const math::float4x4&
	TransformComponent::get_transform_inverse() const noexcept
	{
		this->update_local_transform();
		return local_transform_inverse_;
	}

	void
	TransformComponent::set_world_translate(const math::float3& pos) noexcept
	{
		if (world_translate_ != pos)
		{
			this->on_move_before();

			world_translate_ = pos;
			world_need_updates_ = true;

			this->update_world_children();
			this->on_move_after();
		}
	}

	void
	TransformComponent::set_world_translate_accum(const math::float3& v) noexcept
	{
		this->set_world_translate(world_translate_ + v);
	}

	const math::float3&
	TransformComponent::get_world_translate() const noexcept
	{
		update_world_transform();
		return world_translate_;
	}

	void
	TransformComponent::set_world_scale(const math::float3& pos) noexcept
	{
		if (world_scaling_ != pos)
		{
			this->on_move_before();

			world_scaling_ = pos;
			world_need_updates_ = true;

			this->update_world_children();
			this->on_move_after();
		}
	}

	void
	TransformComponent::set_world_scaleAccum(const math::float3& scale) noexcept
	{
		this->set_world_scale(world_scaling_ + scale);
	}

	const math::float3&
	TransformComponent::get_world_scale() const noexcept
	{
		update_world_transform();
		return world_scaling_;
	}

	void
	TransformComponent::set_world_quaternion(const math::Quaternion& quat) noexcept
	{
		if (world_rotation_ != quat)
		{
			this->on_move_before();

			world_rotation_ = quat;
			world_need_updates_ = true;

			this->update_world_children();
			this->on_move_after();
		}
	}

	void
	TransformComponent::set_world_quaternion_accum(const math::Quaternion& quat) noexcept
	{
		this->set_quaternion(math::cross(quat, world_rotation_));
	}

	const math::Quaternion&
	TransformComponent::get_world_quaternion() const noexcept
	{
		update_world_transform();
		return world_rotation_;
	}

	void
	TransformComponent::set_world_transform(const math::float4x4& transform) noexcept
	{
		this->on_move_before();

		world_transform_ = transform.get_transform(world_translate_, world_rotation_, world_scaling_);
		world_transform_inverse_ = math::transform_inverse(world_transform_);
		world_need_updates_ = false;

		this->update_world_children();
		this->on_move_after();
	}

	void
	TransformComponent::set_world_transform_only_rotate(const math::float4x4& transform) noexcept
	{
		this->on_move_before();

		world_transform_ = transform.get_transform_without_scaler(world_translate_, world_rotation_);
		world_transform_.scale(world_scaling_);
		world_transform_inverse_ = math::transform_inverse(world_transform_);

		world_need_updates_ = false;

		this->update_world_children();
		this->on_move_after();
	}

	const math::float4x4&
	TransformComponent::get_world_transform() const noexcept
	{
		this->update_world_transform();
		return world_transform_;
	}

	const math::float4x4&
	TransformComponent::get_world_transform_inverse() const noexcept
	{
		this->update_world_transform();
		return world_transform_inverse_;
	}

	GameComponentPtr
	TransformComponent::clone() const noexcept
	{
		return std::make_shared<TransformComponent>();
	}

	void
	TransformComponent::on_move_before() except
	{
		this->get_game_object()->on_move_before();
	}

	void
	TransformComponent::on_move_after() except
	{
		this->get_game_object()->on_move_after();
	}

	void
	TransformComponent::update_local_children() const noexcept
	{
		world_need_updates_ = true;

		for (auto& it : this->get_game_object()->get_children())
			it->get_component<TransformComponent>()->update_local_children();
	}

	void
	TransformComponent::update_world_children() const noexcept
	{
		this->update_parent_transform();
		this->update_local_children();
	}

	void
	TransformComponent::update_local_transform() const noexcept
	{
		if (local_need_updates_)
		{
			local_transform_.make_transform(local_translate_, local_rotation_, local_scaling_);
			local_transform_inverse_ = math::transform_inverse(local_transform_);

			local_need_updates_ = false;
		}
	}

	void
	TransformComponent::update_world_transform() const noexcept
	{
		if (world_need_updates_)
		{
			auto parent = this->get_game_object()->get_parent();
			if (parent)
			{
				auto& baseTransform = parent->get_component<TransformComponent>()->get_world_transform();
				world_transform_ = math::transform_multiply(baseTransform, this->get_transform());
				world_transform_.get_transform(world_translate_, world_rotation_, world_scaling_);
				world_transform_inverse_ = math::transform_inverse(world_transform_);
			}
			else
			{
				world_translate_ = local_translate_;
				world_scaling_ = local_scaling_;
				world_rotation_ = local_rotation_;
				world_transform_.make_transform(world_translate_, world_rotation_, world_scaling_);
				world_transform_inverse_ = math::transform_inverse(world_transform_);
			}

			world_need_updates_ = false;
		}
	}

	void
	TransformComponent::update_parent_transform() const noexcept
	{
		if (world_need_updates_)
		{
			world_transform_.make_transform(world_translate_, world_rotation_, world_scaling_);
			world_need_updates_ = false;
		}

		auto parent = this->get_game_object()->get_parent();
		if (parent)
		{
			auto& baseTransformInverse = parent->get_component<TransformComponent>()->get_world_transform_inverse();
			local_transform_ = math::transform_multiply(baseTransformInverse, world_transform_);
			local_transform_.get_transform(local_translate_, local_rotation_, local_scaling_);
		}
		else
		{
			local_scaling_ = world_scaling_;
			local_rotation_ = world_rotation_;
			local_translate_ = world_translate_;
		}
	}
}