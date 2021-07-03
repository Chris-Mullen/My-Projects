#  frozen_string_literal: true

module MusicSortService
  module V1
    # Controller for managing songs
    class SongsController < ApplicationController
      def create
        # Validate artists exist
        params[:artists].each do |a|
          artist = Artist.where(title: a).first
          unless artist
            render_json_not_found_error('artist', a)
            return
          end
        end

        # Validate album exists
        album = Album.where(title: params[:album]).first
        unless album
          render_json_not_found_error('album', params[:album])
          return
        end
        album_id = album.uuid

        # Validate genre exists
        genre = Genre.where(title: params[:genre]).first
        unless genre
          render_json_not_found_error('genre', params[:genre])
          return
        end
        genre_id = genre.uuid

        # Validate Song is not duplicated
        songs = Song.where(album_id: album_id)
        songs.each do |s|
          if s.title == params[:title]
            render_json_duplicate_error(params[:title], params[:album])
            return
          end
        end

        song = Song.create_song(params, genre_id, album_id)
        unless song.save
          render_json_validation_error(song)
          return
        end

        render json: song, status: :created
      end

      def update; end

      def destroy; end

      def show
        render json: Song.where(uuid: params[:song_id])
      end

      def show_all; end
    end
  end
end
