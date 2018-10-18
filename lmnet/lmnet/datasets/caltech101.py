# -*- coding: utf-8 -*-
# Copyright 2018 The Blueoil Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# =============================================================================
from lmnet.datasets.image_folder import ImageFolderBase
import functools
import os
import os.path


class Caltech101(ImageFolderBase):
    extend_dir = "Caltech101/101_ObjectCategories"

    def __init__(
            self,
            subset="train",
            batch_size=100,
            *args,
            **kwargs
    ):
        super().__init__(subset=subset,
                         batch_size=batch_size,
                         *args,
                         **kwargs,
                         )

    @property
    @functools.lru_cache(maxsize=None)
    def classes(self):
        """Returns the classes list in the data set."""

        classes = os.listdir(self.data_dir)
        classes.sort(key=lambda item: item.lower())

        if 'BACKGROUND_Google' in classes:
            classes.remove('BACKGROUND_Google')

        return classes
