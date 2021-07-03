#  frozen_string_literal: true

# Artist serializer definition
class ArtistSerializer < ActiveModel::Serializer
  attributes :uuid, :title, :albums

  def albums; end
end
