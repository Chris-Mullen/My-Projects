#  frozen_string_literal: true

module MusicSortService
  module V1
    # Controller for managing songs
    class SongsController < ApplicationController
      def create
        song = Song.create_song(params)
        unless song.save
          render_json_validation_error(song)
          return
        end

        render json: song, status: :created
      end

      def update; end

      def destroy; end

      def show; end
    end
  end
end
