#  frozen_string_literal: true

# Song serializer definition
class SongSerializer < ActiveModel::Serializer
  attributes :uuid, :title, :comments, :path, :album, :genre, :track, :disk

  def album
    Album.find_by(uuid: object.album_id)
  end

  def genre
    Genre.find_by(uuid: object.genre_id)
  end
end
