#  frozen_string_literal: true

# Album serializer definition
class AlbumSerializer < ActiveModel::Serializer
  attributes :title, :songs, :artists, :year, :tracks, :disks

  def artists; end
  def songs; end
end
