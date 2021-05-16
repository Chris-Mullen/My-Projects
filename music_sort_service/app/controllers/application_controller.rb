#  frozen_string_literal: true

# Parent controller
class ApplicationController < ActionController::API
  # Public: Display error messages in JSON format
  def render_json_validation_error(resource)
    render  status: :bad_request,
            adapter: :json_api,
            serializer: ActiveModel::Serializer::ErrorSerializer,
            json: resource
  end
end
