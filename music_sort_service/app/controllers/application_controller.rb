#  frozen_string_literal: true

# Parent controller
class ApplicationController < ActionController::API
  # Public: Display 400 error messages in JSON format
  def render_json_validation_error(resource)
    render  status: :bad_request,
            adapter: :json_api,
            serializer: ActiveModel::Serializer::ErrorSerializer,
            json: resource
  end

  # Public: Display 404 error messages in JSON format
  def render_json_not_found_error(key, value)
    render  status: :not_found,
            adapter: :json_api,
            json: {key => value}
  end

end
