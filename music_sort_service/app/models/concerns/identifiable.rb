# frozen_string_literal: true

# Public: Concern to ensure a uuid is generated on model creation.
module Identifiable
  extend ActiveSupport::Concern

  included do
    after_validation :assign_identifier, on: :create
  end

  # Public: Set Unique UUid for use as a unique key
  def assign_identifier
    self.uuid ||= SecureRandom.uuid
  end
end
