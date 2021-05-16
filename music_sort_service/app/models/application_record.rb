#  frozen_string_literal: true

# Parent model definition
class ApplicationRecord < ActiveRecord::Base
  self.abstract_class = true
end
