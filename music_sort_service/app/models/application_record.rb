#  frozen_string_literal: true

# Parent model definition
class ApplicationRecord < ActiveRecord::Base
  include Identifiable

  self.abstract_class = true
end
