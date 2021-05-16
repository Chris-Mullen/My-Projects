class AlbumSerializer < ActiveModel::Serializer
  attributes :id, :title, :songs, :artist, :year, :tracks, :disks
end
