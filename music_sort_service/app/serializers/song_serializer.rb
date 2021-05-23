#  frozen_string_literal: true

# Song serializer definition
class SongSerializer < ActiveModel::Serializer
  attributes :uuid, :title, :comments, :path, :artist, :album, :genre, :track, :disk

  def artist; end
  def album; end
  def genre; end
end
